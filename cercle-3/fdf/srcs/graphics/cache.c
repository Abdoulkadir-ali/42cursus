/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:42:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>
#include <immintrin.h> /* AVX Intrinsics */

static t_point	*cached = NULL;
static int		cached_w = 0;
static int		cached_h = 0;
static t_map	*cached_map = NULL;

void	free_cache(void)
{
	if (cached)
	{
		free(cached);
		cached = NULL;
	}
	cached_w = 0;
	cached_h = 0;
	cached_map = NULL;
}

void	cleanup_cache(void)
{
	free_cache();
}

/* Helper to apply final 2D projection (Isometric, etc) after rotation */
static void	finalize_projection(t_point *p, t_camera *cam)
{
	double	tmp_x;
	double	tmp_y;

	/* Apply Projection Formula (Scalar) */
	/* Note: We assume the point is already ROTATED by the AVX loop below */
	
	if (cam->projection == PROJ_ISOMETRIC)
	{
		tmp_x = (p->pos.x - p->pos.y) * 0.866025; /* cos(30) */
		tmp_y = (p->pos.x + p->pos.y) * 0.5 - p->pos.z; /* sin(30) */
		p->pos.x = tmp_x * cam->scale + cam->offset.x;
		p->pos.y = tmp_y * cam->scale + cam->offset.y;
	}
	else if (cam->projection == PROJ_ORTHOGRAPHIC)
	{
		p->pos.x = p->pos.x * cam->scale + cam->offset.x;
		p->pos.y = -p->pos.z * cam->scale + cam->offset.y;
	}
	else
	{
		/* Fallback for complex projections (Perspective, etc) calls standard function */
		/* We de-rotate slightly here for compatibility or just re-project */
		*p = project_point(p->pos, p->color, cam, 0); 
		/* Note: ideally you'd optimize all types, but ISO/ORTHO are 99% of use cases */
	}
}

/* ** SIMD KERNEL 
** Processes 4 points at once.
*/
static void	process_avx_chunk(t_graphics *g, size_t i)
{
	/* Load 4 points (AoS) into Registers */
	/* We use set_pd to load scalar values into vectors manually (Gather) */
	t_vec3d *raw = g->map->points.pos;
	
	__m256d x = _mm256_set_pd(raw[i+3].x, raw[i+2].x, raw[i+1].x, raw[i].x);
	__m256d y = _mm256_set_pd(raw[i+3].y, raw[i+2].y, raw[i+1].y, raw[i].y);
	__m256d z_raw = _mm256_set_pd(raw[i+3].z, raw[i+2].z, raw[i+1].z, raw[i].z);

	/* 1. Apply Z Scaling & Divisor */
	double z_scale_val = g->camera->z_scale;
	if (g->camera->use_z_divisor && g->map->z_divisor != 0)
		z_scale_val /= g->map->z_divisor;
	
	__m256d v_z_scale = _mm256_set1_pd(z_scale_val);
	__m256d z = _mm256_mul_pd(z_raw, v_z_scale);

	/* 2. Center the object */
	__m256d cx = _mm256_set1_pd(g->camera->grid_center.x);
	__m256d cy = _mm256_set1_pd(g->camera->grid_center.y);
	__m256d cz = _mm256_set1_pd(g->camera->grid_center.z);

	x = _mm256_sub_pd(x, cx);
	y = _mm256_sub_pd(y, cy);
	z = _mm256_sub_pd(z, cz);

	/* 3. Apply Rotation Matrix (The Heavy Part) */
	/* x' = x*m00 + y*m01 + z*m02 */
	/* y' = x*m10 + y*m11 + z*m12 */
	/* z' = x*m20 + y*m21 + z*m22 */
	
	__m256d rot00 = _mm256_set1_pd(g->camera->rotation_matrix[0].x);
	__m256d rot01 = _mm256_set1_pd(g->camera->rotation_matrix[0].y);
	__m256d rot02 = _mm256_set1_pd(g->camera->rotation_matrix[0].z);
	
	__m256d rx = _mm256_add_pd(
		_mm256_add_pd(_mm256_mul_pd(x, rot00), _mm256_mul_pd(y, rot01)),
		_mm256_mul_pd(z, rot02));

	__m256d rot10 = _mm256_set1_pd(g->camera->rotation_matrix[1].x);
	__m256d rot11 = _mm256_set1_pd(g->camera->rotation_matrix[1].y);
	__m256d rot12 = _mm256_set1_pd(g->camera->rotation_matrix[1].z);

	__m256d ry = _mm256_add_pd(
		_mm256_add_pd(_mm256_mul_pd(x, rot10), _mm256_mul_pd(y, rot11)),
		_mm256_mul_pd(z, rot12));

	__m256d rot20 = _mm256_set1_pd(g->camera->rotation_matrix[2].x);
	__m256d rot21 = _mm256_set1_pd(g->camera->rotation_matrix[2].y);
	__m256d rot22 = _mm256_set1_pd(g->camera->rotation_matrix[2].z);

	__m256d rz = _mm256_add_pd(
		_mm256_add_pd(_mm256_mul_pd(x, rot20), _mm256_mul_pd(y, rot21)),
		_mm256_mul_pd(z, rot22));

	/* 4. Un-Center */
	x = _mm256_add_pd(rx, cx);
	y = _mm256_add_pd(ry, cy);
	z = _mm256_add_pd(rz, cz);

	/* 5. Store Back (Scatter) */
	/* Use a temporary buffer to extract values from registers */
	double res_x[4], res_y[4], res_z[4];
	_mm256_storeu_pd(res_x, x);
	_mm256_storeu_pd(res_y, y);
	_mm256_storeu_pd(res_z, z);

	int k = 0;
	while (k < 4)
	{
		/* Store rotated 3D coordinates */
		cached[i+k].pos.x = res_x[k];
		cached[i+k].pos.y = res_y[k];
		cached[i+k].pos.z = res_z[k];
		cached[i+k].color = g->map->points.color[i+k];
		
		/* Apply final 2D projection scalar-wise (lightweight) */
		finalize_projection(&cached[i+k], g->camera);
		k++;
	}
}

void	cache_projections(t_graphics *g)
{
	int		w;
	int		h;
	size_t	total;
	size_t	i;

	if (!g || !g->map || !g->camera) return ;
	update_rotation_matrix(g->camera);
	
	w = g->map->width;
	h = g->map->height;
	/* Reallocate cache if map changed */
	if (cached_map != g->map || cached_w != w || cached_h != h)
	{
		cleanup_cache();
		cached = malloc(sizeof(t_point) * (size_t)w * (size_t)h);
		if (!cached) return ;
		cached_w = w;
		cached_h = h;
		cached_map = g->map;
	}

	total = (size_t)w * (size_t)h;
	i = 0;

	/* AVX Loop: Process 4 points at a time */
	while (i + 4 <= total)
	{
		process_avx_chunk(g, i);
		i += 4;
	}

	/* Scalar Cleanup: Process remaining points */
	while (i < total)
	{
		cached[i] = project_point(g->map->points.pos[i],
				g->map->points.color[i], g->camera, g->map->z_divisor);
		i++;
	}
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	size_t	idx;

	if (!g || !g->map) return ((t_point){.pos = {0,0,0}, .color = 0});
	
	/* Check Bounds */
	if (cached && cached_map == g->map && x >= 0 && y >= 0 && x < cached_w && y < cached_h)
	{
		idx = (size_t)y * (size_t)cached_w + (size_t)x;
		return (cached[idx]);
	}
	/* Fallback */
	return (project_point(g->map->points.pos[y * g->map->width + x], 
			g->map->points.color[y * g->map->width + x],
			g->camera, g->map->z_divisor));
}

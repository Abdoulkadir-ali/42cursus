/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:12:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>
#include <stdlib.h>

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

static void	finalize_projection(t_point *p, t_camera *cam)
{
	double	tmp_x;
	double	tmp_y;

	if (cam->projection == PROJ_ISOMETRIC)
	{
		tmp_x = (p->pos.x - p->pos.y) * 0.866025;
		tmp_y = (p->pos.x + p->pos.y) * 0.5 - p->pos.z;
		p->pos.x = tmp_x * cam->scale + cam->offset.x;
		p->pos.y = tmp_y * cam->scale + cam->offset.y;
	}
	else if (cam->projection == PROJ_ORTHOGRAPHIC)
	{
		p->pos.x = p->pos.x * cam->scale + cam->offset.x;
		p->pos.y = -p->pos.z * cam->scale + cam->offset.y;
	}
	else
		*p = project_point(p->pos, p->color, cam, 0);
}

static void	process_avx_chunk(t_graphics *g, size_t i)
{
	t_vec3d	*raw;
	__m256d	x;
	__m256d	y;
	__m256d	z_raw;
	double	z_scale_val;
	__m256d	v_z_scale;
	__m256d	z;
	__m256d	cx;
	__m256d	cy;
	__m256d	cz;
	__m256d	rot00;
	__m256d	rot01;
	__m256d	rot02;
	__m256d	rx;
	__m256d	rot10;
	__m256d	rot11;
	__m256d	rot12;
	__m256d	ry;
	__m256d	rot20;
	__m256d	rot21;
	__m256d	rot22;
	__m256d	rz;
	double	res_x[4], res_y[4], res_z[4];
	int		k;

	raw = g->map->points.pos;
	x = _mm256_set_pd(raw[i + 3].x, raw[i + 2].x, raw[i + 1].x, raw[i].x);
	y = _mm256_set_pd(raw[i + 3].y, raw[i + 2].y, raw[i + 1].y, raw[i].y);
	z_raw = _mm256_set_pd(raw[i + 3].z, raw[i + 2].z, raw[i + 1].z, raw[i].z);
	z_scale_val = g->camera->z_scale;
	if (g->camera->use_z_divisor && g->map->z_divisor != 0)
		z_scale_val /= g->map->z_divisor;
	v_z_scale = _mm256_set1_pd(z_scale_val);
	z = _mm256_mul_pd(z_raw, v_z_scale);
	cx = _mm256_set1_pd(g->camera->grid_center.x);
	cy = _mm256_set1_pd(g->camera->grid_center.y);
	cz = _mm256_set1_pd(g->camera->grid_center.z);
	x = _mm256_sub_pd(x, cx);
	y = _mm256_sub_pd(y, cy);
	z = _mm256_sub_pd(z, cz);
	rot00 = _mm256_set1_pd(g->camera->rotation_matrix[0].x);
	rot01 = _mm256_set1_pd(g->camera->rotation_matrix[0].y);
	rot02 = _mm256_set1_pd(g->camera->rotation_matrix[0].z);
	rx = _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(x, rot00), _mm256_mul_pd(y,
					rot01)), _mm256_mul_pd(z, rot02));
	rot10 = _mm256_set1_pd(g->camera->rotation_matrix[1].x);
	rot11 = _mm256_set1_pd(g->camera->rotation_matrix[1].y);
	rot12 = _mm256_set1_pd(g->camera->rotation_matrix[1].z);
	ry = _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(x, rot10), _mm256_mul_pd(y,
					rot11)), _mm256_mul_pd(z, rot12));
	rot20 = _mm256_set1_pd(g->camera->rotation_matrix[2].x);
	rot21 = _mm256_set1_pd(g->camera->rotation_matrix[2].y);
	rot22 = _mm256_set1_pd(g->camera->rotation_matrix[2].z);
	rz = _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(x, rot20), _mm256_mul_pd(y,
					rot21)), _mm256_mul_pd(z, rot22));
	x = _mm256_add_pd(rx, cx);
	y = _mm256_add_pd(ry, cy);
	z = _mm256_add_pd(rz, cz);
	_mm256_storeu_pd(res_x, x);
	_mm256_storeu_pd(res_y, y);
	_mm256_storeu_pd(res_z, z);
	k = 0;
	while (k < 4)
	{
		cached[i + k].pos.x = res_x[k];
		cached[i + k].pos.y = res_y[k];
		cached[i + k].pos.z = res_z[k];
		cached[i + k].color = g->map->points.color[i + k];
		finalize_projection(&cached[i + k], g->camera);
		k++;
	}
}

void	cache_projections(t_graphics *g)
{
	int		w;
	int		h;
	size_t	total;
	size_t	i;

	if (!g || !g->map || !g->camera)
		return ;
	update_rotation_matrix(g->camera);
	w = g->map->width;
	h = g->map->height;
	if (cached_map != g->map || cached_w != w || cached_h != h)
	{
		cleanup_cache();
		cached = malloc(sizeof(t_point) * (size_t)w * (size_t)h);
		if (!cached)
			return ;
		cached_w = w;
		cached_h = h;
		cached_map = g->map;
	}
	total = (size_t)w * (size_t)h;
	i = 0;
	while (i + 4 <= total)
	{
		process_avx_chunk(g, i);
		i += 4;
	}
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

	if (!g || !g->map)
		return ((t_point){.pos = {0, 0, 0}, .color = 0});
	if (cached && cached_map == g->map && x >= 0 && y >= 0 && x < cached_w
		&& y < cached_h)
	{
		idx = (size_t)y * (size_t)cached_w + (size_t)x;
		return (cached[idx]);
	}
	return (project_point(g->map->points.pos[y * g->map->width + x],
			g->map->points.color[y * g->map->width + x], g->camera,
			g->map->z_divisor));
}

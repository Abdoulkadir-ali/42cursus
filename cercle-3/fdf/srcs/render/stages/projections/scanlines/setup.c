/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:45 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:04:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

static void	setup_simd_rotation(t_simd_ctx *ctx, t_camera *cam)
{
	ctx->rot[0] = _mm256_set1_pd(cam->rotation_matrix[2].x);
	ctx->rot[1] = _mm256_set1_pd(cam->rotation_matrix[2].y);
	ctx->rot[2] = _mm256_set1_pd(cam->rotation_matrix[2].z);
	ctx->vdist = _mm256_set1_pd(cam->view_dist);
}

static void	setup_simd_matrix(t_simd_ctx *ctx, t_matrix4 *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ctx->m[i][j] = _mm256_set1_pd(m->m[i][j]);
			j++;
		}
		i++;
	}
}

static void	setup_simd_center(t_simd_ctx *ctx, t_camera *cam)
{
	t_vec3d	eff_center;

	eff_center = cam->grid_center;
	eff_center.z *= cam->z_scale;
	ctx->cx = _mm256_set1_pd(eff_center.x);
	ctx->cy = _mm256_set1_pd(eff_center.y);
	ctx->cz = _mm256_set1_pd(eff_center.z);
	ctx->z_scale = _mm256_set1_pd(cam->z_scale);
	ctx->off_x = _mm256_set1_pd(cam->offset.x);
	ctx->off_y = _mm256_set1_pd(cam->offset.y);
}

void	setup_simd_constants(t_camera *cam, t_matrix4 *m, t_simd_ctx *ctx)
{
	setup_simd_rotation(ctx, cam);
	setup_simd_matrix(ctx, m);
	setup_simd_center(ctx, cam);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:08:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	apply_scaling_centering(t_simd_batch_ctx *bctx, t_simd_ctx *ctx)
{
	bctx->vz = _mm256_mul_pd(bctx->vz, ctx->z_scale);
	bctx->dx = _mm256_sub_pd(bctx->vx, ctx->cx);
	bctx->dy = _mm256_sub_pd(bctx->vy, ctx->cy);
	bctx->dz = _mm256_sub_pd(bctx->vz, ctx->cz);
}

void	apply_simd_matrix_transform(t_simd_batch_ctx *bctx, t_simd_ctx *ctx)
{
	t_simd_vec3	vec;
	t_simd_vec4	mat_x;
	t_simd_vec4	mat_y;
	t_simd_vec4	mat_w;

	vec.x = bctx->dx;
	vec.y = bctx->dy;
	vec.z = bctx->dz;
	mat_x.m[0] = ctx->m[0][0];
	mat_x.m[1] = ctx->m[0][1];
	mat_x.m[2] = ctx->m[0][2];
	mat_x.m[3] = ctx->m[0][3];
	bctx->res_x = matrix_row_mul(vec, mat_x);
	mat_y.m[0] = ctx->m[1][0];
	mat_y.m[1] = ctx->m[1][1];
	mat_y.m[2] = ctx->m[1][2];
	mat_y.m[3] = ctx->m[1][3];
	bctx->res_y = matrix_row_mul(vec, mat_y);
	mat_w.m[0] = ctx->m[3][0];
	mat_w.m[1] = ctx->m[3][1];
	mat_w.m[2] = ctx->m[3][2];
	mat_w.m[3] = ctx->m[3][3];
	bctx->res_w = matrix_row_mul(vec, mat_w);
}

void	apply_perspective_offsets(t_simd_batch_ctx *bctx, t_simd_ctx *ctx)
{
	bctx->ones = _mm256_set1_pd(1.0);
	bctx->inv_w = _mm256_div_pd(bctx->ones, bctx->res_w);
	bctx->res_x = _mm256_mul_pd(bctx->res_x, bctx->inv_w);
	bctx->res_y = _mm256_mul_pd(bctx->res_y, bctx->inv_w);
	bctx->res_x = _mm256_add_pd(bctx->res_x, ctx->off_x);
	bctx->res_y = _mm256_add_pd(bctx->res_y, ctx->off_y);
}

void	compute_final_z(t_simd_batch_ctx *bctx, t_simd_ctx *ctx)
{
	t_simd_vec3	vec;
	t_simd_vec3	v;

	vec.x = bctx->dx;
	vec.y = bctx->dy;
	vec.z = bctx->dz;
	v.x = ctx->rot[0];
	v.y = ctx->rot[1];
	v.z = ctx->rot[2];
	bctx->final_z = vector_dot(vec, v);
	bctx->final_z = _mm256_sub_pd(bctx->final_z, ctx->vdist);
}

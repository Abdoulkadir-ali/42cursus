/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:01:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	load_simd_vectors(t_simd_batch_ctx *bctx,
		t_transform_batch_ctx *batch_ctx)
{
	bctx->idx = batch_ctx->row_idx + batch_ctx->i;
	bctx->ptr = (double *)&batch_ctx->g->map->points.pos[bctx->idx];
	bctx->vx = _mm256_set_pd(bctx->ptr[9], bctx->ptr[6], bctx->ptr[3],
			bctx->ptr[0]);
	bctx->vy = _mm256_set_pd(bctx->ptr[10], bctx->ptr[7], bctx->ptr[4],
			bctx->ptr[1]);
	bctx->vz = _mm256_set_pd(bctx->ptr[11], bctx->ptr[8], bctx->ptr[5],
			bctx->ptr[2]);
}

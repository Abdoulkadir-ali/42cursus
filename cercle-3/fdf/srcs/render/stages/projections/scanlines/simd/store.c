/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:01:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	transform_simd_batch_store(t_simd_batch_ctx *bctx, t_graphics *g,
		t_point *out)
{
	_mm256_storeu_pd(bctx->buf_x, bctx->res_x);
	_mm256_storeu_pd(bctx->buf_y, bctx->res_y);
	_mm256_storeu_pd(bctx->buf_z, bctx->final_z);
	bctx->k = 0;
	while (bctx->k < 4)
	{
		out[bctx->idx + bctx->k].pos.x = bctx->buf_x[bctx->k];
		out[bctx->idx + bctx->k].pos.y = bctx->buf_y[bctx->k];
		out[bctx->idx + bctx->k].pos.z = bctx->buf_z[bctx->k];
		out[bctx->idx + bctx->k].color = g->map->points.color[bctx->idx
			+ bctx->k];
		if (g->map->points.pos[bctx->idx + bctx->k].z <= BAD_VALUE + 1.0)
			out[bctx->idx + bctx->k].pos = create_vec3d(BAD_VALUE, BAD_VALUE,
					BAD_VALUE);
		bctx->k++;
	}
}

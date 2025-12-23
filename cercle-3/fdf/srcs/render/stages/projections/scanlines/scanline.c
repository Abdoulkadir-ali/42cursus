/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:04:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	transform_scanline(t_graphics *g, t_point *out,
		size_t row_idx, size_t width)
{
	t_transform_scanline_ctx	sctx;

	sctx.cam = g->camera;
	sctx.m = &sctx.cam->transform_matrix;
	setup_simd_constants(sctx.cam, sctx.m, &sctx.ctx);
	sctx.i = 0;
	while (sctx.i < width - 3)
	{
		sctx.batch_ctx.g = g;
		sctx.batch_ctx.out = out;
		sctx.batch_ctx.row_idx = row_idx;
		sctx.batch_ctx.i = sctx.i;
		sctx.batch_ctx.ctx = &sctx.ctx;
		transform_simd_batch(&sctx.batch_ctx);
		sctx.i += 4;
	}
	sctx.rem_ctx.g = g;
	sctx.rem_ctx.out = out;
	sctx.rem_ctx.row_idx = row_idx;
	sctx.rem_ctx.i = sctx.i;
	sctx.rem_ctx.width = width;
	handle_remainder(&sctx.rem_ctx);
}

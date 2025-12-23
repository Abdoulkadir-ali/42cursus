/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   batch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:01:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	transform_simd_batch(t_transform_batch_ctx *batch_ctx)
{
	t_simd_batch_ctx	bctx;

	load_simd_vectors(&bctx, batch_ctx);
	apply_scaling_centering(&bctx, batch_ctx->ctx);
	apply_simd_matrix_transform(&bctx, batch_ctx->ctx);
	apply_perspective_offsets(&bctx, batch_ctx->ctx);
	compute_final_z(&bctx, batch_ctx->ctx);
	transform_simd_batch_store(&bctx, batch_ctx->g, batch_ctx->out);
}

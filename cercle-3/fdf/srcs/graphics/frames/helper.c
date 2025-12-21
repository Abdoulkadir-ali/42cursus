/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:12:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>

void	clear_z_buffer_simd(t_clear_z_ctx *ctx)
{
	ctx->i = 0;
	while (ctx->i < ctx->total - 7)
	{
		_mm256_storeu_ps(&ctx->z_buffer[ctx->i], ctx->max_depth);
		ctx->i += 8;
	}
}

void	clear_z_buffer_remainder(t_clear_z_ctx *ctx)
{
	while (ctx->i < ctx->total)
		ctx->z_buffer[ctx->i++] = 1e30f;
}

void	clear_image_simd(t_clear_img_ctx *ctx)
{
	ctx->i = 0;
	while (ctx->i < ctx->total_bytes - 31)
	{
		_mm256_storeu_si256((__m256i *)&ctx->buffer[ctx->i], ctx->zeros);
		ctx->i += 32;
	}
}

void	clear_image_remainder(t_clear_img_ctx *ctx)
{
	while (ctx->i < ctx->total_bytes)
		ctx->buffer[ctx->i++] = 0;
}

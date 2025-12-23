/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:48:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	clear_z_buffer(t_graphics *g)
{
	t_clear_z_ctx	ctx;

	if (!g->window->z_buffer)
		return ;
	ctx.total = g->window->width * g->window->height;
	ctx.z_buffer = g->window->z_buffer;
	ctx.max_depth = _mm256_set1_ps(1e30f);
	clear_z_buffer_simd(&ctx);
	clear_z_buffer_remainder(&ctx);
}

void	clear_image(t_graphics *g)
{
	t_clear_img_ctx	ctx;

	ctx.total_bytes = g->window->height * g->window->main_img.img_line_len;
	ctx.buffer = g->window->main_img.img_addr;
	ctx.zeros = _mm256_setzero_si256();
	clear_image_simd(&ctx);
	clear_image_remainder(&ctx);
}

void	clear_frame_buffers(t_graphics *g)
{
	if (g->window->main_img.img_addr)
		clear_image(g);
	if (g->render_config.use_depth_culling && g->window->z_buffer)
		clear_z_buffer(g);
}

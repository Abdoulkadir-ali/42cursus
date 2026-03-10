/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:57:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>

/**
 * @brief Convert projected endpoints into integer screen-space line data.
 * @param start Start point.
 * @param end End point.
 * @param dlc Line context to populate.
 */
void	set_line_positions(t_point start, t_point end, t_draw_line_ctx *dlc)
{
	dlc->start_pos.x = (int)start.pos.x;
	dlc->start_pos.y = (int)start.pos.y;
	dlc->end_pos.x = (int)end.pos.x;
	dlc->end_pos.y = (int)end.pos.y;
	dlc->delta.x = abs(dlc->end_pos.x - dlc->start_pos.x);
	dlc->delta.y = abs(dlc->end_pos.y - dlc->start_pos.y);
	if (dlc->start_pos.x < dlc->end_pos.x)
		dlc->sign.x = 1;
	else
		dlc->sign.x = -1;
	if (dlc->start_pos.y < dlc->end_pos.y)
		dlc->sign.y = 1;
	else
		dlc->sign.y = -1;
}

/**
 * @brief Check whether the line start point lies inside the target image.
 * @param dlc Prepared line context.
 * @return `1` when the start point is inside the image, otherwise `0`.
 */
int	is_line_visible(t_draw_line_ctx *dlc)
{
	if (dlc->start_pos.x < 0 || dlc->start_pos.x >= (int)dlc->ctx.width
		|| dlc->start_pos.y < 0 || dlc->start_pos.y >= (int)dlc->ctx.height)
		return (0);
	return (1);
}

/**
 * @brief Resolve the initial pixel and z-buffer addresses for a line.
 * @param g Graphics state providing image and z-buffer storage.
 * @param dlc Line context to update.
 */
void	set_line_pointers(t_graphics *g, t_draw_line_ctx *dlc)
{
	dlc->pixel_addr = g->window->main_img.img_addr + (dlc->start_pos.y
			* dlc->ctx.line_len) + (dlc->start_pos.x * dlc->ctx.bpp);
	dlc->z_addr = NULL;
	if (g->window->z_buffer)
		dlc->z_addr = g->window->z_buffer + (dlc->start_pos.y * dlc->ctx.width)
			+ dlc->start_pos.x;
	if (dlc->delta.x > dlc->delta.y)
		dlc->steps = dlc->delta.x;
	else
		dlc->steps = dlc->delta.y;
}

/**
 * @brief Build the full line rasterization context from two projected points.
 * @param g Graphics state providing image and z-buffer data.
 * @param start Start point.
 * @param end End point.
 * @param dlc Output line context.
 * @return `1` when the line should be drawn, otherwise `0`.
 */
int	init_draw_line_ctx(t_graphics *g, t_point start, t_point end,
		t_draw_line_ctx *dlc)
{
	set_line_positions(start, end, dlc);
	setup_pointers(g, &dlc->ctx, dlc->sign.x, dlc->sign.y);
	if (!is_line_visible(dlc))
		return (0);
	set_line_pointers(g, dlc);
	init_interpolation(start, end, dlc->steps, &dlc->interp);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:46:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:59:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int	get_bresenham_flags(t_graphics *g)
{
	int	flags;

	flags = 0;
	if (g->render_config.use_depth_culling)
		flags |= B_USE_Z;
	if (g->camera->color_shift.x || g->camera->color_shift.y
		|| g->camera->color_shift.z)
		flags |= B_COLOR_SHIFT;
	return (flags);
}

void	draw_line_clipped(t_graphics *g, t_point start, t_point end,
		t_clipping_bounds bounds)
{
	t_draw_line_ctx	dlc;
	int				flags;

	if (!init_draw_line_ctx(g, start, end, &dlc))
		return ;
	fill_bresenham_params(&dlc);
	dlc.p.min_x = bounds.min_x;
	dlc.p.max_x = bounds.max_x;
	flags = get_bresenham_flags(g);
	if (g->render_config.use_horizon_culling)
		bresenham_raycast(g, &dlc.p, flags);
	else
		bresenham(g, &dlc.p, flags);
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_clipping_bounds	bounds;

	bounds = (t_clipping_bounds){0, g->window->width};
	draw_line_clipped(g, start, end, bounds);
}

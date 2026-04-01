/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:18:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Cache state for hover optimization (P4).
*/

bool	update_hover(t_gui *gui, t_render *render)
{
	t_hit	hit;
	t_ray	ray;
	t_panel	panel;

	if (gui->input.mouse_x != gui->hover.x || gui->input.mouse_y != gui->hover.y
		|| gui->render.dirty)
	{
		gui->hover.x = gui->input.mouse_x;
		gui->hover.y = gui->input.mouse_y;
		make_camera_ray(render, gui->hover.x * gui->win.width / gui->win.disp_w,
			gui->hover.y * gui->win.height / gui->win.disp_h, &ray);
		ft_memset(&hit, 0, sizeof(t_hit));
		gui->hover.active = bvh_intersect(gui->scene->bvh, &ray, &hit);
	}
	if (gui->hover.active)
	{
		panel = (t_panel){.x = gui->hover.x + 16, .y = gui->hover.y + 16,
			.w = 180, .h = 40, .bg = COL_BG, .brd = COL_HOVER,
			.pos = vec2i(gui->hover.x + 16, gui->hover.y + 16),
			.size = vec2i(180, 40)};
		draw_panel(gui, panel);
		return (true);
	}
	return (false);
}

void	draw_hover_text(t_gui *gui)
{
	if (gui->hover.active)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, gui->hover.x + 28,
			gui->hover.y + 40, COL_HOVER, "Object hit");
	}
}

void	handle_hover(t_gui *gui, t_render *render)
{
	if (update_hover(gui, render))
		draw_hover_text(gui);
}

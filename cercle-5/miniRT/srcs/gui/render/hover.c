/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:18:00 by abdoali          ###   ########.fr       */
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

	if (gui->input.mouse.x != gui->hover.mouse.x
		|| gui->input.mouse.y != gui->hover.mouse.y
		|| gui->render.dirty)
	{
		gui->hover.mouse = gui->input.mouse;
		make_camera_ray(render, (double)gui->hover.mouse.x * gui->win.size.x
			/ gui->win.disp_size.x,
			(double)gui->hover.mouse.y * gui->win.size.y
			/ gui->win.disp_size.y, &ray);
		ft_memset(&hit, 0, sizeof(t_hit));
		gui->hover.active = bvh_intersect(gui->scene->bvh, &ray, &hit);
	}
	if (gui->hover.active)
	{
		panel = (t_panel){
			.pos = vec2i(gui->hover.mouse.x + 16, gui->hover.mouse.y + 16),
			.size = vec2i(180, 40), .bg = COL_BG, .brd = COL_HOVER};
		draw_panel(gui, panel);
		return (true);
	}
	return (false);
}

void	draw_hover_text(t_gui *gui)
{
	if (gui->hover.active)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, gui->hover.mouse.x + 28,
			gui->hover.mouse.y + 40, COL_HOVER, "Object hit");
	}
}

void	handle_hover(t_gui *gui, t_render *render)
{
	if (update_hover(gui, render))
		draw_hover_text(gui);
}

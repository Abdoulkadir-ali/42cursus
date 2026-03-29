/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** Cache state for hover optimization (P4).
*/

bool	update_hover(t_gui *gui, t_render *ctx)
{
	t_hit	hit;
	t_ray	ray;
	t_panel	panel;

	if (gui->input.mouse.x != gui->hover->pos.x
		|| gui->input.mouse.y != gui->hover->pos.y)
	{
		gui->hover->pos.x = gui->input.mouse.x;
		gui->hover->pos.y = gui->input.mouse.y;
		make_camera_ray(ctx, gui->hover->pos.x * gui->win.size.x
			/ gui->win.disp_size.x, gui->hover->pos.y * gui->win.size.y
			/ gui->win.disp_size.y, &ray);
		ft_memset(&hit, 0, sizeof(t_hit));
		gui->hover->active = bvh_intersect(gui->rt.bvh, &ray, &hit);
	}
	if (gui->hover->active)
	{
		panel = (t_panel){.box = (t_gui_box){vec2i(gui->hover->pos.x + 16,
			gui->hover->pos.y + 16), vec2i(180, 40)}, .bg = COL_BG,
			.brd = COL_HOVER};
		draw_panel(gui, panel);
		return (true);
	}
	return (false);
}

void	draw_hover_text(t_gui *gui)
{
	if (gui->hover->active)
	{
		gui_draw_string(gui, "Object hit", gui->hover->pos.x + 28,
			gui->hover->pos.y + 40, COL_HOVER);
	}
}

void  handle_hover(t_gui *gui, t_render *ctx)
{
	if (update_hover(gui, ctx))
		draw_hover_text(gui);
}

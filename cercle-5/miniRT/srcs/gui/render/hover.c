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

#include "gui.h"

t_hover_cache	g_hover;

/*
** Cache state for hover optimization (P4).
*/

bool	update_hover(t_gui *gui, t_render_ctx *ctx)
{
	t_hit	hit;
	t_ray	ray;
	t_panel	panel;

	if (gui->input.mouse_x != g_hover.x || gui->input.mouse_y != g_hover.y
		|| gui->render.dirty)
	{
		g_hover.x = gui->input.mouse_x;
		g_hover.y = gui->input.mouse_y;
		make_camera_ray(ctx, g_hover.x * gui->win.width / gui->win.disp_w,
			g_hover.y * gui->win.height / gui->win.disp_h, &ray);
		ft_memset(&hit, 0, sizeof(t_hit));
		g_hover.active = bvh_intersect(gui->scene->bvh, &ray, &hit);
	}
	if (g_hover.active)
	{
		panel = (t_panel){.x=g_hover.x+16, .y=g_hover.y+16, .w=180, .h=40, .bg=COL_BG, .brd=COL_HOVER, .pos=vec2i(g_hover.x+16,g_hover.y+16), .size=vec2i(180,40)};
		draw_panel(gui, panel);
		return (true);
	}
	return (false);
}

void	draw_hover_text(t_gui *gui)
{
	if (g_hover.active)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, g_hover.x + 28,
			g_hover.y + 40, COL_HOVER, "Object hit");
	}
}

void	handle_hover(t_gui *gui, t_render_ctx *ctx)
{
	if (update_hover(gui, ctx))
		draw_hover_text(gui);
}

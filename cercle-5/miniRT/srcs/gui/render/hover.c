/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Cache state for hover optimization (P4).
*/
static struct s_hover_cache
{
	int		x;
	int		y;
	bool	active;
	bool	hit;
	long	last_frame;
}	g_hover;

/*
** Updates hover state and draws panel if hit.
** Returns true if a hit occurred (to draw text later).
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
		make_camera_ray(ctx, g_hover.x, g_hover.y, &ray);
		ft_memset(&hit, 0, sizeof(t_hit));
		g_hover.active = bvh_intersect(gui->bvh, &ray, &hit);
	}
	if (g_hover.active)
	{
		panel = (t_panel){g_hover.x + 20, g_hover.y + 20, 220, 100,
			0x050505, 0x00D0D0};
		draw_panel(gui, panel);
		return (true);
	}
	return (false);
}

void	draw_hover_text(t_gui *gui)
{
	if (g_hover.active)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, g_hover.x + 35,
			g_hover.y + 55, 0x00D0D0, "OBJECT HIT");
	}
}

/*
** Legacy wrapper if needed, or update render.c to use above.
*/
void	handle_hover(t_gui *gui, t_render_ctx *ctx)
{
	if (update_hover(gui, ctx))
		draw_hover_text(gui);
}

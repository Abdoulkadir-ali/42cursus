/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 22:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, t_vec2i pos)
{
	int			col;
	size_t	*dst;

	col = panel_color(panel, pos);
	if (col == -1)
		return ;
	dst = (size_t *)(gui->win.disp_addr + (pos.y * gui->win.disp_line_len
				+ pos.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.85f);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	t_vec2i	pos;

	pos.y = panel.pos.y;
	while (pos.y < panel.pos.y + panel.size.y)
	{
		pos.x = panel.pos.x;
		while (pos.x < panel.pos.x + panel.size.x)
		{
			draw_panel_pixel(gui, panel, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_ui_panels(t_gui *gui)
{
	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
}

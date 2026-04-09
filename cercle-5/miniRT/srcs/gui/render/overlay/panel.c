/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, t_vec2i pos)
{
	int			col;
	uint32_t	*dst;

	col = panel_color(panel, pos);
	if (col == -1)
		return ;
	dst = (uint32_t *)(gui->win.disp_addrs[gui->render.back_idx]
			+ (pos.y * gui->win.disp_line_len
				+ pos.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.85f);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	t_vec2i	pos;
	t_vec2i	end;

	end.x = panel.pos.x + panel.size.x;
	end.y = panel.pos.y + panel.size.y;
	pos.y = panel.pos.y;
	while (pos.y < end.y)
	{
		pos.x = panel.pos.x;
		while (pos.x < end.x)
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

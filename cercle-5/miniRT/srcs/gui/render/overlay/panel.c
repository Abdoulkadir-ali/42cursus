/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, int i, int j)
{
	char	*dst;
	int		col;
	float	a;

	if (i < 0 || i >= gui->win.disp_size.x)
		return ;
	if (j < 0 || j >= gui->win.disp_size.y)
		return ;
	col = panel_color(panel, i, j);
	if (col == -1)
		return ;
	dst = gui->win.disp_addr + (j * gui->win.disp_line_len + i * 4);
	a = 0.85;
	if (col == panel.brd)
		a = 0.95;
	*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	int	i;
	int	j;

	j = panel.box.pos.y;
	while (j < panel.box.pos.y + panel.box.size.y)
	{
		i = panel.box.pos.x;
		while (i < panel.box.pos.x + panel.box.size.x)
		{
			draw_panel_pixel(gui, panel, i, j);
			i++;
		}
		j++;
	}
}

void	draw_ui_panels(t_gui *gui)
{
	t_panel	panel;
	int		bh;

	bh = gui->win.disp_size.y;
	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
	panel = (t_panel){.box = {vec2i(SCENE_PANEL_W + 8, bh - 68),
		vec2i(340, 52)}, .bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, panel);
	panel = (t_panel){.box = {vec2i(gui->win.disp_size.x - 112, 16),
		vec2i(96, 32)}, .bg = COL_BG, .brd = COL_FPS};
	draw_panel(gui, panel);
}

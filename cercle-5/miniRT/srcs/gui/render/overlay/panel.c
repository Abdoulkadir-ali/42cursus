/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:20:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, int i, int j)
{
	char	*dst;
	int		col;
	float	a;

	if (i < 0 || i >= gui->win.disp_w || j < 0 || j >= gui->win.disp_h)
		return ;
	col = panel_color(panel, i, j);
	if (col == -1)
		return ;
	dst = gui->win.disp_addr + (j * gui->win.disp_line_len + i * 4);
	a = 0.75;
	if (col == panel.brd)
		a = 0.90;
	*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	int	i;
	int	j;

	j = panel.y;
	while (j < panel.y + panel.h)
	{
		i = panel.x;
		while (i < panel.x + panel.w)
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

	bh = gui->win.disp_h;
	panel = (t_panel){.x = 16, .y = 16, .w = 310, .h = 120, .bg = COL_BG,
		.brd = COL_ACCENT, .pos = vec2i(16, 16), .size = vec2i(310, 120)};
	draw_panel(gui, panel);
	panel = (t_panel){.x = 16, .y = bh - 72, .w = 460, .h = 56, .bg = COL_BG,
		.brd = COL_BORDER, .pos = vec2i(16, bh - 72), .size = vec2i(460, 56)};
	draw_panel(gui, panel);
	panel = (t_panel){.x = gui->win.disp_w - 120, .y = 16, .w = 104, .h = 40,
		.bg = COL_BG, .brd = COL_FPS, .pos = vec2i(gui->win.disp_w - 120, 16),
		.size = vec2i(104, 40)};
	draw_panel(gui, panel);
}

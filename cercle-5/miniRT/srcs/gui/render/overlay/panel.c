/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 20:41:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_panel_pixel(t_gui *gui, t_panel panel, t_vec2i pos)
{
	char	*dst;
	int		col;
	float	a;

	if (pos.x < 0 || pos.x >= gui->win.disp_size.x
		|| pos.y < 0 || pos.y >= gui->win.disp_size.y)
		return ;
	col = panel_color(panel, pos);
	if (col == -1)
		return ;
	dst = gui->win.disp_addr + (pos.y * gui->win.disp_line_len + pos.x * 4);
	a = 0.75;
	if (col == panel.brd)
		a = 0.90;
	*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
}

void	draw_panel(t_gui *gui, t_panel panel)
{
	t_vec2i	p;

	p.y = panel.pos.y;
	while (p.y < panel.pos.y + panel.size.y)
	{
		p.x = panel.pos.x;
		while (p.x < panel.pos.x + panel.size.x)
		{
			draw_panel_pixel(gui, panel, p);
			p.x++;
		}
		p.y++;
	}
}

void	draw_ui_panels(t_gui *gui)
{
	t_panel	panel;
	int		bh;

	bh = gui->win.disp_size.y;
	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
	panel = (t_panel){
		.pos = vec2i(16, bh - 72), .size = vec2i(460, 56),
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, panel);
	panel = (t_panel){
		.pos = vec2i(gui->win.disp_size.x - 120, 16), .size = vec2i(104, 40),
		.bg = COL_BG, .brd = COL_FPS};
	draw_panel(gui, panel);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:55:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	phit(t_vec2i m, t_vec2i pos, t_vec2i size)
{
	if (m.x < pos.x || m.x >= pos.x + size.x)
		return (false);
	if (m.y < pos.y || m.y >= pos.y + size.y)
		return (false);
	return (true);
}

void	draw_modal_bg(t_gui *gui, int h, t_vec2i *p)
{
	t_panel	dim;
	t_panel	box;

	dim = (t_panel){
		.pos = vec2i(0, 0),
		.size = vec2i(gui->win.disp_size.x, gui->win.disp_size.y),
		.bg = 0x0D0D14, .brd = 0x0D0D14};
	draw_panel(gui, dim);
	p->x = (gui->win.disp_size.x - POPUP_W) / 2;
	p->y = (gui->win.disp_size.y - h) / 2;
	box = (t_panel){
		.pos = *p, .size = vec2i(POPUP_W, h),
		.bg = 0x1A1A28, .brd = COL_ACCENT};
	draw_panel(gui, box);
}

void	draw_popup_btn(t_gui *gui, t_panel btn)
{
	draw_panel(gui, btn);
	if (btn.lbl && *btn.lbl)
		mlx_string_put(gui->win.mlx, gui->win.win,
			btn.pos.x + 8, btn.pos.y + btn.size.y / 2 + 4, COL_TEXT,
			(char *)btn.lbl);
}

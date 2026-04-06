/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	fill_rect_row(t_gui *gui, t_vec2i pos, size_t w, unsigned int col)
{
	char	*dst;
	size_t	i;

	if (pos.y >= (int)gui->win.disp_size.y)
		return ;
	i = 0;
	while (i < w)
	{
		if ((pos.x + (int)i) < (int)gui->win.disp_size.x)
		{
			dst = gui->win.disp_addrs[gui->render.back_idx]
				+ (pos.y * gui->win.disp_line_len + (pos.x + (int)i) * 4);
			*(unsigned int *)dst = col;
		}
		i++;
	}
}

void	fill_rect(t_gui *gui, t_vec2i pos, t_vec2s size, unsigned int col)
{
	size_t	j;

	j = 0;
	while (j < size.y)
	{
		fill_rect_row(gui, vec2i(pos.x, pos.y + (int)j), size.x, col);
		j++;
	}
}

void	draw_slider_fill(t_gui *gui, t_vec2i pos, int fill_w, int total_w)
{
	int	knob_x;

	fill_rect(gui, pos, ui_size((size_t)total_w, 8, gui->win.disp_size),
		(unsigned int)COL_SLIDER_BG);
	fill_rect(gui, pos, ui_size((size_t)total_w, 1, gui->win.disp_size),
		(unsigned int)COL_BORDER);
	fill_rect(gui, vec2i(pos.x, pos.y + 7),
		ui_size((size_t)total_w, 1, gui->win.disp_size),
		(unsigned int)COL_BORDER);
	if (fill_w > 0)
		fill_rect(gui, pos, ui_size((size_t)fill_w, 8, gui->win.disp_size),
			(unsigned int)COL_SLIDER_FG);
	knob_x = pos.x + fill_w - 1;
	if (knob_x < pos.x)
		knob_x = pos.x;
	fill_rect(gui, vec2i(knob_x, pos.y - 2),
		ui_size(3, 12, gui->win.disp_size), COL_SLIDER_KNOB);
}

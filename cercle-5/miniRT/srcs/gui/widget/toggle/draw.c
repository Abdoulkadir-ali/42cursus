/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_draw_toggle(t_gui *gui, t_widget *w)
{
	t_panel			p;
	int				bg;
	t_vec2i			lpos;
	const char		*state;
	int				state_col;

	bg = 0x402020;
	state = "OFF";
	state_col = 0xFF5050;
	if (w->value)
	{
		bg = 0x206040;
		state = " ON";
		state_col = 0x40FF80;
	}
	p = (t_panel){.pos = w->pos, .size = w->size, .bg = bg, .brd = COL_BORDER};
	draw_panel(gui, p);
	lpos = vec2i(w->pos.x + 4, w->pos.y + w->size.y / 2 - 4);
	if (w->label)
	{
		gui_draw_string(gui, w->label, lpos, COL_TEXT);
		lpos.x += ft_strlen(w->label) * 8 + 8;
	}
	gui_draw_string(gui, state, lpos, state_col);
}

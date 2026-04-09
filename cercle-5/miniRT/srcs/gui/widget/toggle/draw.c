/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	get_toggle_style(t_widget *w, int *bg, const char **state,
	int *state_col)
{
	*bg = COL_TOGGLE_OFF_BG;
	*state = "OFF";
	*state_col = COL_TOGGLE_OFF_TEXT;
	if (w->value)
	{
		*bg = COL_TOGGLE_ON_BG;
		*state = " ON";
		*state_col = COL_TOGGLE_ON_TEXT;
	}
}

void	widget_draw_toggle(t_gui *gui, t_widget *w)
{
	t_panel			p;
	int				bg;
	t_vec2i			lpos;
	const char		*state;
	int				state_col;

	get_toggle_style(w, &bg, &state, &state_col);
	p.pos = w->pos;
	p.size = w->size;
	p.bg = bg;
	p.brd = COL_BORDER;
	p.lbl = NULL;
	draw_panel(gui, p);
	lpos = vec2i(w->pos.x + 4, w->pos.y + w->size.y / 2 - 4);
	if (w->label)
	{
		gui_draw_string(gui, w->label, lpos, COL_TEXT);
		lpos.x += ft_strlen(w->label) * 8 + 8;
	}
	gui_draw_string(gui, state, lpos, state_col);
}

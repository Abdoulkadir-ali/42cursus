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

void	widget_draw_button(t_gui *gui, t_widget *w)
{
	t_panel	p;
	t_vec2i	lpos;

	p = (t_panel){.pos = w->pos, .size = w->size,
		.bg = 0x2A2A40, .brd = COL_ACCENT};
	draw_panel(gui, p);
	if (w->label)
	{
		lpos = vec2i(w->pos.x + w->size.x / 2 - ft_strlen(w->label) * 4,
				w->pos.y + w->size.y / 2 - 4);
		gui_draw_string(gui, w->label, lpos, COL_TEXT);
	}
}

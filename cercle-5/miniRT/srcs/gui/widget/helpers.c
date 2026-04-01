/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:41:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	gui_label(struct s_gui *gui, const char *text, t_vec2i pos)
{
	gui_draw_string(gui, text, pos.x, pos.y, COL_TEXT);
}

void	gui_slider(struct s_gui *gui, double *val, double min, double max,
		t_vec2i pos, const char *fmt)
{
	char	buf[64];

	(void)min;
	(void)max;
	snprintf(buf, sizeof(buf), fmt, *val);
	gui_draw_string(gui, buf, pos.x, pos.y, COL_TEXT);
}

void	gui_panel(struct s_gui *gui, t_vec2i pos, t_vec2i size, const char *title)
{
	t_panel	p;

	p = (t_panel){.x = pos.x, .y = pos.y, .w = size.x, .h = size.y,
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, p);
	gui_draw_string(gui, title, pos.x + 8, pos.y + 6, COL_TEXT);
}

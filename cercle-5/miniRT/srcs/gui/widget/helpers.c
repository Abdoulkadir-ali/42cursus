/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	gui_label(struct s_gui *gui, const char *text, t_vec2i pos)
{
	gui_draw_string(gui, text, pos, COL_TEXT);
}

void	gui_panel(struct s_gui *gui, t_vec2i pos, t_vec2s size,
			const char *title)
{
	t_panel	p;

	p = (t_panel){.pos = pos, .size = size,
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, p);
	gui_draw_string(gui, title, vec2i(pos.x + 8, pos.y + 6), COL_TEXT);
}

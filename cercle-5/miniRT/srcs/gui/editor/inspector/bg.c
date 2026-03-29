/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_inspector_header(t_gui *gui, int x, int w)
{
	t_panel	header;

	header = (t_panel){.box = (t_gui_box){vec2i(x, 0), vec2i(w, HEADER_H)},
		.bg = COL_HEADER, .brd = COL_BORDER};
	draw_panel(gui, header);
}

void	draw_inspector_bg(t_gui *gui)
{
	t_panel	panel;
	int		x;
	int		w;
	int		h;

	if (!gui->inspector->visible || !gui->selection->active)
		return ;
	w = gui->inspector->box.size.x;
	h = gui->win.disp_size.y;
	x = gui->win.disp_size.x - w;
	panel = (t_panel){.box = (t_gui_box){vec2i(x, 0), vec2i(w, h)},
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, panel);
	draw_inspector_header(gui, x, w);
}

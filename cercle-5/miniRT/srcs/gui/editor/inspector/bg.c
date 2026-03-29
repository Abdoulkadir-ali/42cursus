/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
}

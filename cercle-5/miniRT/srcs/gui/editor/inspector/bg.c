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

#include "gui.h"

void	draw_inspector_bg(t_gui *gui)
{
	t_panel	panel;
	int		x;
	int		w;
	int		h;

	if (!gui->inspector.visible || !gui->selection.active)
		return ;
	w = gui->inspector.width;
	h = gui->win.disp_h;
	x = gui->win.disp_w - w;
	panel = (t_panel){.x = x, .y = 0, .w = w, .h = h, .bg = COL_BG,
		.brd = COL_BORDER, .pos = vec2i(x, 0), .size = vec2i(w, h)};
	draw_panel(gui, panel);
}

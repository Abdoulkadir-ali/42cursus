/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:14:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_transform_panel(t_gui *gui, t_vec2i pos)
{
	t_vec2i	d;
	t_vec2i	p;

	d = gui->win.disp_size;
	p.x = pos.x + ui_sx(8, d);
	p.y = ui_sy(92, d);
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2i){p.x, p.y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &p);
	transform_selection_sync(gui);
}


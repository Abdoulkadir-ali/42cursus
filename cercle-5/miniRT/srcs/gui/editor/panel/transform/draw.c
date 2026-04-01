/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 21:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_transform_panel(t_gui *gui, t_vec2i pos)
{
	t_vec2i	p;

	p = pos;
	p.x += 8;
	p.y = 88;
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2i){p.x, p.y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &p);
	transform_selection_sync(gui);
}

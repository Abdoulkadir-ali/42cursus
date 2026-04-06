/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:22:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	transform_panel(t_gui *gui)
{
	t_vec2i	p;
	t_vec2s	panel_size;

	panel_size = (t_vec2s){200, 300};
	gui_panel(gui, (t_vec2i){10, 10}, panel_size, "Transform");
	p.x = 10;
	p.y = 35;
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2i){20, p.y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &p);
}

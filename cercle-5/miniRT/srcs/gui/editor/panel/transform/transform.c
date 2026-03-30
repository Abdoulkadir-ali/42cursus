/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:58:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	transform_panel(t_gui *gui)
{
	int		y;
	t_vec2	panel_size;

	panel_size = (t_vec2){200, 300};
	gui_panel(gui, (t_vec2){10, 10}, panel_size, "Transform");
	y = 35;
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2){20, y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &y);
	transform_selection_sync(gui);
}

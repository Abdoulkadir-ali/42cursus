/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	transform_panel(t_gui *gui)
{
	int		y;
	t_vec2i	panel_size;

	panel_size = (t_vec2i){200, 300};
	gui_panel(gui, (t_vec2i){10, 10}, panel_size, "Transform");
	y = 35;
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2i){20, y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &y);
	transform_selection_sync(gui);
}

void	draw_transform_panel(t_gui *gui, int x)
{
	int		y;

	(void)x;
	y = 35;
	if (!gui->selection.active)
	{
		gui_label(gui, "No selection", (t_vec2i){20, y});
		return ;
	}
	build_tr_sliders(gui, gui->selection.type, &y);
	transform_selection_sync(gui);
}

bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	(void)gui;
	(void)mouse;
	return (false);
}

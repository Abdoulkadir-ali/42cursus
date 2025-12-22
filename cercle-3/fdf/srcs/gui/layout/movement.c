/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_projection_display_layout(t_layout *l, t_gui *gui)
{
	// MODE Display
	char	*names[PROJ_COUNT];
	names[0] = "PARALLEL";
	names[1] = "CONIC";
	gui_layout_title(l, "MODE");
	gui_layout_key_value(l, "Type (P):", names[gui->camera->projection]);
	
	// ALPHA Display
	char buffer[20];
	char *label = (gui->camera->projection == PROJ_PARALLEL) ? "Incidence (A):" : "FOV (A):";
	
	format_number((int)gui->camera->alpha, buffer);
	gui_layout_key_value(l, label, buffer);
}

void	draw_speed_display_layout(t_layout *l, t_gui *gui)
{
	char	move_str[10];
	char	zoom_str[10];
	char	rot_str[10];

	gui_layout_title(l, "SPEEDS");
	format_speed(gui->camera->move_speed, move_str);
	gui_layout_key_value(l, "Move:", move_str);
	format_speed(gui->camera->zoom_speed, zoom_str);
	gui_layout_key_value(l, "Zoom:", zoom_str);
	format_speed(gui->camera->rotation_speed / DEFAULT_ROTATION_SPEED, rot_str);
	gui_layout_key_value(l, "Rotation:", rot_str);
}

void	draw_map_name_display_layout(t_layout *l, t_gui *gui)
{
	char	*map_name;

	gui_layout_title(l, "MAP");
	if (gui->maps->map_files && gui->maps->current_index >= 0
		&& (size_t)gui->maps->current_index < gui->maps->count)
	{
		map_name = gui->maps->map_files[gui->maps->current_index];
		gui_layout_label(l, map_name);
	}
	else
		gui_layout_label(l, "Test Grid");
}

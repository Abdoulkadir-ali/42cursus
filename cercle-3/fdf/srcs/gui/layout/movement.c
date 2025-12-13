/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:56:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_projection_display_layout(t_layout *l, t_gui *gui)
{
	char	*names[PROJ_COUNT];

	names[0] = "Isometric";
	names[1] = "Orthographic";
	names[2] = "Perspective";
	names[3] = "Oblique";
	names[4] = "Camera Matrix";
	names[5] = "Nonlinear";
	gui_layout_title(l, "PROJECTION");
	gui_layout_label(l, names[gui->camera->projection]);
}

void	draw_speed_display_layout(t_layout *l, t_gui *gui)
{
	char	move_str[10];
	char	zoom_str[10];

	gui_layout_title(l, "SPEEDS");
	format_speed(gui->camera->move_speed, move_str);
	gui_layout_key_value(l, "Move:", move_str);
	format_speed(gui->camera->zoom_speed, zoom_str);
	gui_layout_key_value(l, "Zoom:", zoom_str);
}

void	draw_map_name_display_layout(t_layout *l, t_gui *gui)
{
	char	*map_name;

	gui_layout_title(l, "MAP");
	if (gui->maps->map_files && gui->maps->current_index >= 0
		&& gui->maps->current_index < gui->maps->count)
	{
		map_name = gui->maps->map_files[gui->maps->current_index];
		gui_layout_label(l, map_name);
	}
	else
		gui_layout_label(l, "Test Grid");
}

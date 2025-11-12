/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 20:21:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


void	draw_projection_display_at(t_gui *gui, int *section_y)
{
	int		y;
	char	*names[PROJ_COUNT] = {"Isometric", "Orthographic", "Perspective", "Oblique",
		"Camera Matrix", "Nonlinear"};

	y = *section_y;
	put_colored(gui, GUI_PADDING, y, "PROJECTION", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	put_value(gui, GUI_PADDING + 10, y, names[gui->camera->projection]);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_speed_display_at(t_gui *gui, int *section_y)
{
	int		y;
	char	move_str[10];
	char	zoom_str[10];

	y = *section_y;
	put_colored(gui, GUI_PADDING, y, "SPEEDS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	put_text(gui, GUI_PADDING, y, "Move:");
	format_speed(gui->camera->move_speed, move_str);
	put_value(gui, GUI_PADDING + 100, y, move_str);
	y += GUI_LINE_HEIGHT;
	put_text(gui, GUI_PADDING, y, "Zoom:");
	format_speed(gui->camera->zoom_speed, zoom_str);
	put_value(gui, GUI_PADDING + 100, y, zoom_str);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_map_name_display_at(t_gui *gui, int *section_y)
{
	int		y;
	char	*map_name;

	y = *section_y;
	put_colored(gui, GUI_PADDING, y, "MAP", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (gui->map_manager->map_files && gui->map_manager->current_index >= 0
		&& gui->map_manager->current_index < gui->map_manager->count)
	{
		map_name = gui->map_manager->map_files[gui->map_manager->current_index];
		put_value(gui, GUI_PADDING + 10, y, map_name);
	}
	else
		put_value(gui, GUI_PADDING + 10, y, "Test Grid");
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}


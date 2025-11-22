/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:26:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 14:26:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


void	draw_projection_display_at(t_data *data, int *section_y)
{
	int		y;
	char	*names[PROJ_COUNT] = {"Isometric", "Orthographic", "Perspective", "Oblique",
		"Camera Matrix", "Nonlinear"};
	y = *section_y;
	put_colored(&data->gui, GUI_PADDING, y, (t_colored_text){"PROJECTION", GUI_TITLE_COLOR});
	y += GUI_TITLE_HEIGHT;
	put_value(data, GUI_PADDING + 10, y, names[data->camera.projection]);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_speed_display_at(t_data *data, int *section_y)
{
	int		y;
	char	move_str[10];
	char	zoom_str[10];

	y = *section_y;
	put_colored(&data->gui, GUI_PADDING, y, (t_colored_text){"SPEEDS", GUI_TITLE_COLOR});
	y += GUI_TITLE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Move:");
	format_speed(data->camera.move_speed, move_str);
	put_value(data, GUI_PADDING + 100, y, move_str);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Zoom:");
	format_speed(data->camera.zoom_speed, zoom_str);
	put_value(data, GUI_PADDING + 100, y, zoom_str);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_map_name_display_at(t_data *data, int *section_y)
{
	int		y;
	char	*map_name;

	y = *section_y;
	put_colored(&data->gui, GUI_PADDING, y, (t_colored_text){"MAP", GUI_TITLE_COLOR});
	y += GUI_TITLE_HEIGHT;
	if (data->map_manager.map_files && data->map_manager.current_index >= 0
		&& data->map_manager.current_index < data->map_manager.count)
	{
		map_name = data->map_manager.map_files[data->map_manager.current_index];
		put_value(data, GUI_PADDING + 10, y, map_name);
	}
	else
		put_value(data, GUI_PADDING + 10, y, "Test Grid");
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}
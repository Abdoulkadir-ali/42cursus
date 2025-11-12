/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:53:29 by abdoali          #+#    #+#             */
/*   Updated: 2025/11/12 19:53:29 by abdoali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


static void	format_depth_str(int percent, char *str)
{
	str[0] = '0' + (percent / 10);
	str[1] = '0' + (percent % 10);
	str[2] = '%';
	str[3] = ' ';
	str[4] = 'v';
	str[5] = 'i';
	str[6] = 's';
	str[7] = 'i';
	str[8] = 'b';
	str[9] = 'l';
	str[10] = 'e';
	str[11] = '\0';
}

void	draw_dampening_display(t_data *data)
{
	int		y;
	char	depth_str[20];
	int		visible_percent;

	y = data->window.height - 240;
	put_colored(data, GUI_PADDING, y, "DEPTH DAMPENING", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (data->camera.dampening_threshold <= data->map->min_z)
		put_value(data, GUI_PADDING + 10, y, "OFF");
	else
	{
		visible_percent = (int)(100.0 * (data->map->max_z
					- data->camera.dampening_threshold) / (data->map->max_z
					- data->map->min_z));
		format_depth_str(visible_percent, depth_str);
		put_value(data, GUI_PADDING + 10, y, depth_str);
	}
}

void	draw_style_display(t_data *data)
{
	int		y;
	int		accent;
	char	*names[GUI_STYLE_COUNT] = {"TRON BLUE", "TRON ORANGE", "MATRIX", "CYBERPUNK", "NEON GRID"};
	y = data->window.height - 240;
	accent = get_gui_theme(data->camera.gui_style).accent;
	put_colored(data, GUI_PADDING, y, "GUI STYLE", accent);
	y += GUI_TITLE_HEIGHT;
	put_colored(data, GUI_PADDING + 10, y, names[data->camera.gui_style],
		accent);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_performance_part1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:03:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_performance_header(t_data *data, int *y)
{
	put_colored(data, GUI_PADDING, *y, "OPTIMIZATIONS", GUI_TITLE_COLOR);
	*y += GUI_TITLE_HEIGHT;
}

void	draw_performance_counts(t_data *data, int *y)
{
	char	buffer[50];
	int		total;
	int		rendered;

	total = data->map->width * data->map->height;
	if (data->lod_level > 0)
		rendered = total / (data->lod_level * data->lod_level);
	else
		rendered = total;
	put_text(data, GUI_PADDING, *y, "Total:");
	format_number(total, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, *y, "Rendered:");
	format_number(rendered, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT + 5;
}

void	draw_performance_lod(t_data *data, int *y)
{
	char	buffer[50];

	put_text(data, GUI_PADDING, *y, "LOD (L):");
	format_number(data->lod_level, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}

void	draw_performance_z_scale(t_data *data, int *y)
{
	char	buffer[50];

	put_text(data, GUI_PADDING, *y, "Z-Scale (Z):");
	format_float(data->camera.z_scale, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}

void	draw_performance_z_divisor(t_data *data, int *y)
{
	put_text(data, GUI_PADDING, *y, "Z-Divisor (X):");
	if (data->camera.use_z_divisor)
		put_value(data, GUI_PADDING + 120, *y, "ON");
	else
		put_value(data, GUI_PADDING + 120, *y, "OFF");
	*y += GUI_LINE_HEIGHT;
}
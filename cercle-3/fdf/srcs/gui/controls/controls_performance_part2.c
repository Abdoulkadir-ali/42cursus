/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_performance_part2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:04:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_performance_triangles(t_data *data, int *y)
{
	char	buffer[50];
	int		triangles;

	triangles = (data->map->width - 1) * (data->map->height - 1) * 2;
	put_text(data, GUI_PADDING, *y, "Triangles:");
	format_number(triangles, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}

void	draw_performance_fps(t_data *data, int *y)
{
	char	buffer[50];

	put_text(data, GUI_PADDING, *y, "FPS:");
	format_number(data->fps, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}
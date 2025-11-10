/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_style_apply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 18:18:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map_style.h"

int	get_map_point_color(int z, int min_z, int max_z, t_map_style style)
{
	return (get_map_line_color(z, min_z, max_z, style));
}

void	cycle_map_style(t_data *data)
{
	data->map_config.style = (data->map_config.style + 1) % MAP_STYLE_COUNT;
	apply_map_style(data);
}

void	apply_map_style(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			data->map->points[y][x].color = get_map_line_color(
					data->map->points[y][x].pos.z,
					data->map->min_z,
					data->map->max_z,
					data->map_config.style);
			x++;
		}
		y++;
	}
}

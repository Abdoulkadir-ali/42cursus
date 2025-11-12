/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:14:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	cycle_map_style(t_data *data)
{
	data->map_config.style = (data->map_config.style + 1) % MAP_STYLE_COUNT;
	apply_map_style(data);
}

void	apply_map_style(t_data *data)
{
	int		x;
	int		y;
	t_vec3	v;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			v = create_vec3(data->map->points[y][x].pos.z, data->map->min_z,
					data->map->max_z);
			data->map->points[y][x].color = get_map_line_color(v,
					data->map_config.style);
			x++;
		}
		y++;
	}
}

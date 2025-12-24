/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:29:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	apply_colors(t_map *map)
{
	t_vec3	pos;
	t_vec3	color;
	int		idx;

	pos.y = 0;
	while (pos.y < (int)map->height)
	{
		pos.x = 0;
		while (pos.x < (int)map->width)
		{
			idx = (int)pos.y * map->width + (int)pos.x;
			color = get_height_color(map->points.raw[idx].z, map->min_max_z.x,
					map->min_max_z.y);
			map->points.color[idx] = color;
			pos.x++;
		}
		pos.y++;
	}
}

t_vec3	get_map_line_color(t_vec3 v, t_map_style style)
{
	if (style == MAP_STYLE_GRADIENT)
		return (get_height_color(v.x, v.y, v.z));
	else if (style == MAP_STYLE_SOLID)
		return (get_solid_color(v.x));
	else if (style == MAP_STYLE_ZEBRA)
		return (get_zebra_color(v.x));
	else if (style == MAP_STYLE_NEON)
		return (get_neon_color(v.x));
	return (create_color(255, 255, 255));
}

void	apply_map_style(t_map *map)
{
	t_vec3	pos;
	t_vec3	v;
	t_vec3	color;
	int		idx;

	pos.y = 0;
	while (pos.y < (int)map->height)
	{
		pos.x = 0;
		while (pos.x < (int)map->width)
		{
			idx = (int)pos.y * map->width + (int)pos.x;
			if (map->style.style == MAP_STYLE_RAW)
			{
				map->points.color[idx] = map->points.source_color[idx];
			}
			else
			{
				v = create_vec3(map->points.raw[idx].z, map->min_max_z.x,
						map->min_max_z.y);
				color = get_map_line_color(v, map->style.style);
				map->points.color[idx] = color;
			}
			pos.x++;
		}
		pos.y++;
	}
}

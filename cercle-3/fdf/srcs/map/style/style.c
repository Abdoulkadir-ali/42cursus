/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 02:32:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	cycle_map_style(t_map_manager *m)
{
	t_map_style_config	c;

	if (!m->maps || m->count == 0)
		return ;
	c = m->maps[m->current_index]->style;
	c.style = (c.style + 1) % MAP_STYLE_COUNT;
	m->maps[m->current_index]->style = c;
}

void	apply_colors(t_map *map)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			color = get_height_color(map->points.raw[y][x].z, map->min_z, map->max_z);
			map->points.color[y][x] = color;
			x++;
		}
		y++;
	}
}

int	get_map_line_color(t_vec3 v, t_map_style style)
{
	if (style == MAP_STYLE_GRADIENT)
		return (get_height_color(v.x, v.y, v.z));
	else if (style == MAP_STYLE_SOLID)
		return (get_solid_color(v.x));
	else if (style == MAP_STYLE_ZEBRA)
		return (get_zebra_color(v.x));
	else if (style == MAP_STYLE_NEON)
		return (get_neon_color(v.x));
	return (0xFFFFFF);
}

#include <stdio.h>


void	apply_map_style(t_map *map)
{
	int		x;
	int		y;
	t_vec3	v;
	int		color;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			v = create_vec3(map->points.raw[y][x].z, map->min_z, map->max_z);
			color = get_map_line_color(v, map->style.style);
			map->points.color[y][x] = color;
			x++;
		}
		y++;
	}
}

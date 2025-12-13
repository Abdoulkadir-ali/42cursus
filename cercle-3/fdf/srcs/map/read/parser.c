/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:33:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	get_map_dimensions(int fd, int *width, int *height)
{
	char	*line;
	int		curr_w;

	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			(*height)++;
			curr_w = count_words(line);
			if (curr_w > *width)
				*width = curr_w;
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	allocate_map_points(t_map *map)
{
	size_t	total;
	size_t	i;

	total = (size_t)map->height * (size_t)map->width;
	map->points.pos = malloc(sizeof(t_vec3d) * total);
	map->points.raw = malloc(sizeof(t_vec3d) * total);
	map->points.color = malloc(sizeof(int) * total);
	if (!map->points.pos || !map->points.raw || !map->points.color)
		return (0);
	i = 0;
	while (i < total)
	{
		map->points.raw[i].z = BAD_VALUE;
		map->points.raw[i].x = i % map->width;
		map->points.raw[i].y = i / map->width;
		map->points.color[i] = 0xFFFFFF;
		i++;
	}
	return (1);
}

void	parse_map_data(t_map *map, int fd)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		if (!is_empty_line(line))
		{
			parse_line(line, map, y);
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

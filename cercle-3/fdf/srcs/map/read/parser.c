/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:55:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

static char *skip_spaces(char *p)
{
	while (p && *p && (*p == ' ' || *p == '\t' || *p == '\r'))
		p++;
	return (p);
}

void	get_map_dimensions(int fd, int *width, int *height)
{
	char	*line;
	char	*p;

	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			(*height)++;
			if (*width == 0)
			{
				p = line;
				while (*p && *p != '\n')
				{
					p = skip_spaces(p);
					if (*p == '\0' || *p == '\n')
						break;
					(*width)++;
					while (*p && *p != '\n' && *p != ' ' && *p != '\t')
						p++;
				}
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	allocate_map_points(t_map *map)
{
	int	y;
	int	x;

	map->points.pos = malloc(sizeof(t_vec3d *) * map->height);
	if (!map->points.pos)
		return (0);
	map->points.raw = malloc(sizeof(t_vec3d *) * map->height);
	if (!map->points.raw)
		return (0);
	map->points.color = malloc(sizeof(int *) * map->height);
	if (!map->points.color)
		return (0);
	y = 0;
	while (y < map->height)
	{
		map->points.pos[y] = malloc(sizeof(t_vec3d) * map->width);
		if (!map->points.pos[y])
			return (0);
		map->points.raw[y] = malloc(sizeof(t_vec3d) * map->width);
		if (!map->points.raw[y])
			return (0);
		map->points.color[y] = malloc(sizeof(int) * map->width);
		if (!map->points.color[y])
			return (0);
		x = 0;
		while (x < map->width)
		{
			map->points.raw[y][x].x = x;
			map->points.raw[y][x].y = y;
			map->points.raw[y][x].z = 0;
			map->points.color[y][x] = 0xFFFFFF;
			x++;
		}
		y++;
	}
	return (1);
}

void	parse_map_data(t_map *map, int fd)
{
	char    *line;
	char    *p;
	char    *end;
	int     x;
	int     y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		if (line[0] != '\n')
		{
			p = line;
			x = 0;
			while (x < map->width)
			{
				p = skip_spaces(p);
				if (!p || *p == '\0' || *p == '\n')
					break;
				/* parse z (decimal, possibly negative) */
				long z = strtol(p, &end, 10);
				if (end == p)
					z = 0;
				map->points.raw[y][x].z = (int)z;
				p = end;
				/* optional color after comma: allow hex (0x..) or decimal */
				if (*p == ',')
				{
					p++;
					long color = strtol(p, &end, 0);
					if (end == p)
						color = 0xFFFFFF;
					map->points.color[y][x] = (int)color;
					p = end;
				}
				x++;
			}
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
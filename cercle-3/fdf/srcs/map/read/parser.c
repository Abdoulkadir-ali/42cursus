/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:33:51 by abdoali          ###   ########.fr       */
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
	int	total;

	total = map->height * map->width;
	map->points.pos = malloc(sizeof(t_vec3d) * total);
	if (!map->points.pos)
		return (0);
	map->points.raw = malloc(sizeof(t_vec3d) * total);
	if (!map->points.raw)
		return (0);
	map->points.color = malloc(sizeof(int) * total);
	if (!map->points.color)
		return (0);
	int i = 0;
	while (i < total)
	{
		map->points.raw[i].x = i % map->width;
		map->points.raw[i].y = i / map->width;
		map->points.raw[i].z = 0;
		map->points.color[i] = 0xFFFFFF;
		i++;
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
				int index = y * map->width + x;
				p = skip_spaces(p);
				if (!p || *p == '\0' || *p == '\n')
					break;
				/* parse z (decimal, possibly negative) */
				long z = strtol(p, &end, 10);
				if (end == p)
					z = 0;
				map->points.raw[index].z = (int)z;
				p = end;
				/* optional color after comma: allow hex (0x..) or decimal */
				if (*p == ',')
				{
					p++;
					long color = strtol(p, &end, 0);
					if (end == p)
						color = 0xFFFFFF;
					map->points.color[index] = (int)color;
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
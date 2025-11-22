/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:03:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <limits.h>

#define BAD_VALUE -2000000000.0

static char	*skip_spaces(char *p)
{
	while (p && *p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\v'
			|| *p == '\f'))
		p++;
	return (p);
}

static int	count_words(char *line)
{
	int		count;
	char	*p;

	count = 0;
	p = skip_spaces(line);
	while (p && *p && *p != '\n')
	{
		count++;
		while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r')
			p++;
		p = skip_spaces(p);
	}
	return (count);
}

void	get_map_dimensions(int fd, int *width, int *height)
{
	char	*line;
	int		curr_w;

	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0')
		{
			if (line[0] == '\n' && line[1] == '\0')
			{
				free(line);
				line = get_next_line(fd);
				continue;
			}
			
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
	int	y;

	map->points.pos = malloc(sizeof(t_vec3d *) * map->height);
	map->points.raw = malloc(sizeof(t_vec3d *) * map->height);
	map->points.color = malloc(sizeof(int *) * map->height);

	if (!map->points.pos || !map->points.raw || !map->points.color)
		return (0);

	y = 0;
	while (y < map->height)
	{
		map->points.pos[y] = malloc(sizeof(t_vec3d) * map->width);
		map->points.raw[y] = malloc(sizeof(t_vec3d) * map->width);
		map->points.color[y] = malloc(sizeof(int) * map->width);

		if (!map->points.pos[y] || !map->points.raw[y] || !map->points.color[y])
			return (0); // Cleanup would be needed in real implementation

		y++;
	}
	return (1);
}

void	parse_map_data(t_map *map, int fd)
{
	char	*line;
	char	*p;
	char	*end;
	int		x;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		if (line[0] != '\n' && line[0] != '\0')
		{
			p = line;
			x = 0;
			while (x < map->width)
			{
				p = skip_spaces(p);
				if (!p || *p == '\0' || *p == '\n')
					break ;
				
				long z = strtol(p, &end, 10);
				if (end == p)
					z = 0;
				
				map->points.raw[y][x].z = (double)z;
				map->points.raw[y][x].x = x;
				map->points.raw[y][x].y = y;
				map->points.color[y][x] = 0xFFFFFF;
				
				p = end;
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
			// Pad remaining columns with zeros if line is shorter
			while (x < map->width)
			{
				map->points.raw[y][x].z = 0;
				map->points.raw[y][x].x = x;
				map->points.raw[y][x].y = y;
				map->points.color[y][x] = 0xFFFFFF;
				x++;
			}
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
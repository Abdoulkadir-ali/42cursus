/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:10:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <limits.h>

/* Define Magic Number locally if not in header */
#ifndef BAD_VALUE
# define BAD_VALUE -2000000000.0
#endif

static char	*skip_spaces(char *p)
{
	while (p && *p && (*p == ' ' || *p == '\t' || *p == '\r'
			|| *p == '\v' || *p == '\f'))
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

/* 1. SCAN PASS: Find the absolute maximum width */
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
			/* Ignore empty lines at end of file */
			if (line[0] == '\n' && line[1] == '\0')
			{
				free(line);
				line = get_next_line(fd);
				continue ;
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

/* 2. ALLOCATION: Allocate ONE block and PAD with BAD_VALUE */
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
		/* CRITICAL: Initialize everything to BAD_VALUE.
		   If a line is shorter than map->width, the tail remains BAD_VALUE. */
		map->points.raw[i].z = BAD_VALUE;
		
		/* Pre-calculate grid coordinates for the cache */
		map->points.raw[i].x = i % map->width;
		map->points.raw[i].y = i / map->width;
		
		map->points.color[i] = 0xFFFFFF;
		i++;
	}
	return (1);
}

/* 3. PARSING: Fill the data we have, leave the rest as BAD_VALUE */
void	parse_map_data(t_map *map, int fd)
{
	char	*line;
	char	*p;
	char	*end;
	int		x;
	int		y;
	size_t	idx;

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
				/* If line ends early, STOP. The rest is already BAD_VALUE */
				if (!p || *p == '\0' || *p == '\n')
					break ;
				
				/* Calculate 1D Index */
				idx = (size_t)y * map->width + x;

				long z = strtol(p, &end, 10);
				if (end == p) z = 0;

				map->points.raw[idx].z = (double)z;
				
				p = end;
				if (*p == ',')
				{
					p++;
					long color = strtol(p, &end, 0);
					if (end == p) color = 0xFFFFFF;
					map->points.color[idx] = (int)color;
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
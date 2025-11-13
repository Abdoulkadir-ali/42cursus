/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 02:18:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <fcntl.h>
#include <unistd.h>

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	count_words(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

void	get_map_dimensions(int fd, int *width, int *height)
{
	char	*line;
	char	**split;

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
				split = ft_split(line, ' ');
				*width = count_words(split);
				free_split(split);
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
	char *line;
	char **split;
	char **parts;
	int x;
	int y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		if (line[0] != '\n')
		{
			split = ft_split(line, ' ');
			x = 0;
			while (split[x] && x < map->width)
			{
				if (ft_strchr(split[x], ','))
				{
					parts = ft_split(split[x], ',');
					map->points.raw[y][x].z = ft_atoi(parts[0]);
					map->points.color[y][x] = ft_atoi(parts[1]);
					free_split(parts);
				}
				else
					map->points.raw[y][x].z = ft_atoi(split[x]);
				x++;
			}
			free_split(split);
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
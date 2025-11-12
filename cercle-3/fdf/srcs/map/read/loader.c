/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:55:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>

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

static void	get_map_dimensions(int fd, int *width, int *height)
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

static int	allocate_map_points(t_map *map)
{
	int	y;
	int	x;

	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (0);
	y = 0;
	while (y < map->height)
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (0);
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].pos.x = x;
			map->points[y][x].pos.y = y;
			map->points[y][x].pos.z = 0;
			map->points[y][x].color = 0xFFFFFF;
			x++;
		}
		y++;
	}
	return (1);
}

static void	parse_map_data(t_map *map, int fd)
{
	char	*line;
	char	**split;
	int		x;
	int		y;

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
				map->points[y][x].pos.z = ft_atoi(split[x]);
				x++;
			}
			free_split(split);
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

static void	apply_colors(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].color = get_height_color(map->points[y][x].pos.z,
					map->min_z, map->max_z);
			x++;
		}
		y++;
	}
}

t_map	*load_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (create_test_grid());
	get_map_dimensions(fd, &width, &height);
	close(fd);
	if (width == 0 || height == 0)
		return (create_test_grid());
	map = malloc(sizeof(t_map));
	if (!map)
		return (create_test_grid());
	map->width = width;
	map->height = height;
	if (!allocate_map_points(map))
		return (free_map(map), create_test_grid());
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_map(map), create_test_grid());
	parse_map_data(map, fd);
	close(fd);
	calculate_min_max_z(map);
	apply_colors(map);
	return (map);
}

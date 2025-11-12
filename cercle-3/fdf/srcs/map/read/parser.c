/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:25:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 19:28:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
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

void	parse_map_data(t_map *map, int fd)
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
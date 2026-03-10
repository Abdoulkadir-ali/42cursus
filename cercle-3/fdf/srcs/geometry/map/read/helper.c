/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:08:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Advance past horizontal whitespace characters.
 * @param p String cursor to move forward.
 * @return Pointer to the next non-space character.
 */
char	*skip_spaces(char *p)
{
	while (p && *p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\v'
			|| *p == '\f'))
		p++;
	return (p);
}

/**
 * @brief Count numeric tokens on one map line.
 * @param line Raw line from the map file.
 * @return Number of point tokens on the line.
 */
int	count_words(char *line)
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

/**
 * @brief Check whether a line only contains the final newline.
 * @param line Raw line from the map file.
 * @return `1` when the line is empty, otherwise `0`.
 */
int	is_empty_line(char *line)
{
	return (line[0] == '\n' && line[1] == '\0');
}

/**
 * @brief Parse one point token into height and optional color.
 * @param p Cursor positioned at the point token.
 * @param map Map being filled.
 * @param idx Linear point index to update.
 * @return Cursor advanced past the parsed token.
 */
char	*parse_point(char *p, t_map *map, size_t idx)
{
	char	*end;
	long	z;
	long	color;

	z = strtol(p, &end, 10);
	if (end == p)
		z = 0;
	map->points.raw[idx].z = (double)z;
	p = end;
	if (*p == ',')
	{
		p++;
		color = strtol(p, &end, 0);
		if (end == p)
			color = 0xFFFFFF;
		map->points.color[idx] = int_color_to_rgb((unsigned int)color);
		map->points.source_color[idx] = map->points.color[idx];
		p = end;
	}
	else
		map->points.source_color[idx] = create_color(255, 255, 255);
	return (p);
}

/**
 * @brief Parse one logical row of the map file.
 * @param line Raw row contents.
 * @param map Map being filled.
 * @param y Target row index in the map.
 */
void	parse_line(char *line, t_map *map, int y)
{
	char	*p;
	size_t	x;
	size_t	idx;

	p = line;
	x = 0;
	while (x < map->width)
	{
		p = skip_spaces(p);
		if (!p || *p == '\0' || *p == '\n')
			break ;
		idx = (size_t)y * map->width + x;
		p = parse_point(p, map, idx);
		x++;
	}
}

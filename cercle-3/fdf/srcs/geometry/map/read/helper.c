/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:08:41 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

char	*skip_spaces(char *p)
{
	while (p && *p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\v'
			|| *p == '\f'))
		p++;
	return (p);
}

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

int	is_empty_line(char *line)
{
	return (line[0] == '\n' && line[1] == '\0');
}

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
		map->points.color[idx] = (int)color;
		p = end;
	}
	return (p);
}

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

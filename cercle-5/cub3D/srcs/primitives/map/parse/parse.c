/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:44:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parser.h"

static int	build_and_validate(t_map *map, char **raw, size_t n)
{
	if (build_grid(map, raw, n) == 0)
	{
		free_raw(raw, n);
		free_map(map);
		return (0);
	}
	free_raw(raw, n);
	compute_door_axes(map);
	return (validate_map(map));
}

int	parse_map(const char *path, t_map *map)
{
	t_parser	parser;
	char		**raw_lines;
	t_vec3s		c;

	ft_bzero(map, sizeof(t_map));
	map->floor_color.x = -1.0f;
	map->ceil_color.x = -1.0f;
	raw_lines = NULL;
	c.x = 0;
	c.y = 0;
	if (!parser_init(&parser, path))
		return (0);
	if (process_line(&parser, map, &raw_lines, &c) == 0)
	{
		parser_close(&parser);
		free_raw(raw_lines, c.y);
		free_map(map);
		return (0);
	}
	parser_close(&parser);
	return (build_and_validate(map, raw_lines, c.y));
}

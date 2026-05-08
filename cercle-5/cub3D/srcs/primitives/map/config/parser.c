/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	parse_config_line(const char *line, t_map *map)
{
	int	r;

	while (*line != '\0' && ft_isspace((unsigned char)*line) != 0)
		line++;
	r = parse_wall_line(map, line);
	if (r != -1)
		return (r);
	if (ft_strncmp(line, "R", 1) == 0
		&& ft_isspace((unsigned char)line[1]) != 0)
		return (parse_resolution_line(line + 1));
	if (ft_strncmp(line, "S", 1) == 0
		&& ft_isspace((unsigned char)line[1]) != 0)
		return (parse_sprite_line(map, line + 1));
	if (ft_strncmp(line, "F", 1) == 0
		&& ft_isspace((unsigned char)line[1]) != 0)
		return (parse_floor_line(map, line + 1));
	if (ft_strncmp(line, "C", 1) == 0
		&& ft_isspace((unsigned char)line[1]) != 0)
		return (parse_ceil_line(map, line + 1));
	return (0);
}

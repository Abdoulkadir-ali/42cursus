/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	parse_floor_line(t_map *map, const char *line)
{
	if (parse_rgb_safe(line, &map->floor_color) != 0)
		return (1);
	return (parse_texture_path(map, TEX_FLOOR, line));
}

int	parse_ceil_line(t_map *map, const char *line)
{
	if (parse_rgb_safe(line, &map->ceil_color) != 0)
		return (1);
	return (parse_texture_path(map, TEX_CEIL, line));
}

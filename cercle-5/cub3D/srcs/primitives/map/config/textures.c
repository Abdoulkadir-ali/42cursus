/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	set_texture(t_map *map, int type, const char *line)
{
	if (map->tex_paths[type] != NULL)
		return (0);
	return (parse_texture_path(map, type, line));
}

int	parse_wall_line(t_map *map, const char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0
		&& ft_isspace((unsigned char)line[2]) != 0)
		return (set_texture(map, TEX_NO, line + 2));
	if (ft_strncmp(line, "SO", 2) == 0
		&& ft_isspace((unsigned char)line[2]) != 0)
		return (set_texture(map, TEX_SO, line + 2));
	if (ft_strncmp(line, "WE", 2) == 0
		&& ft_isspace((unsigned char)line[2]) != 0)
		return (set_texture(map, TEX_WE, line + 2));
	if (ft_strncmp(line, "EA", 2) == 0
		&& ft_isspace((unsigned char)line[2]) != 0)
		return (set_texture(map, TEX_EA, line + 2));
	if (ft_strncmp(line, "DO", 2) == 0
		&& ft_isspace((unsigned char)line[2]) != 0)
		return (set_texture(map, TEX_DOOR, line + 2));
	return (-1);
}

int	parse_sprite_line(t_map *map, const char *line)
{
	return (set_texture(map, TEX_SPRITE, line));
}

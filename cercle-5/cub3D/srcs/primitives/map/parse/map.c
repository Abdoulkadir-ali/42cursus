/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:00:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "pathfinder.h"

static int	validate_single_texture(const char *path)
{
	if (!!ft_strnstr(path, ".xpm", ft_strlen(path)))
	{
		if (!validate_xpm_file(path))
		{
			print_error("Invalid XPM file: %s", path);
			return (0);
		}
		return (1);
	}
	print_error("Unsupported texture format: %s", path);
	return (0);
}

static int	validate_texture_paths(t_map *map)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (map->tex_paths[i] && !validate_single_texture(map->tex_paths[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!map)
		return (0);
	if (!validate_texture_paths(map))
		return (0);
	if (!pf_check_closed(map))
	{
		print_error("Invalid map: not closed by walls");
		return (0);
	}
	if (!pf_validate_map(map, map->player_spawn.pos))
	{
		print_error("Invalid map: unreachable play area");
		return (0);
	}
	return (1);
}

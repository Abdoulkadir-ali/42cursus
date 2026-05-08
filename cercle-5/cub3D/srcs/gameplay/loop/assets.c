/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:34:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:31:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"

int	load_map_textures(t_map *map, t_world *world, t_app *app)
{
	size_t	i;

	if (map == NULL)
		return (0);
	i = 0;
	while (i < TEX_COUNT)
	{
		if (map->tex_paths[i] != NULL
			&& load_texture(&map->textures[i], map->tex_paths[i],
				world, app) == 0)
			return (0);
		i++;
	}
	return (1);
}

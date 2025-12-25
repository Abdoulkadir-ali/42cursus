/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 22:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 23:18:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "geometry.h"

static t_gen_params	create_gen_params(t_map *current_map, int generated_id)
{
	t_gen_params	params;
	int				seed;

	params.width = current_map->width;
	params.height = current_map->height;
	if (params.width < 50)
		params.width = 50;
	if (params.height < 50)
		params.height = 50;
	seed = time(NULL) + generated_id;
	srand(seed);
	params.scale = 2.0 + (rand() % 60) / 10.0;
	params.z_scale = 10.0 + (rand() % 30);
	params.octaves = 3 + (rand() % 4);
	params.persistence = 0.3 + (rand() % 40) / 100.0;
	params.seed = seed;
	return (params);
}

static void	replace_current_map(t_maps *maps, t_map *new_map)
{
	size_t	i;
	int		is_current_map_loaded;

	if (!new_map || !maps)
		return ;
	is_current_map_loaded = 0;
	i = 0;
	while (i < maps->count)
	{
		if (maps->maps[i++] == maps->current_map)
		{
			is_current_map_loaded = 1;
			break ;
		}
	}
	if (maps->current_map && !is_current_map_loaded)
		free_map(maps->current_map);
	maps->current_map = new_map;
	maps->generated_id++;
}

t_map	*generate_and_replace_map(t_maps *maps)
{
	t_gen_params	params;
	t_map			*new_map;

	if (!maps || !maps->current_map)
		return (NULL);
	if (maps->is_generating)
		return (NULL);
	maps->is_generating = 1;
	params = create_gen_params(maps->current_map, maps->generated_id);
	new_map = generate_runtime_map(params);
	if (!new_map)
	{
		maps->is_generating = 0;
		return (NULL);
	}
	replace_current_map(maps, new_map);
	maps->is_generating = 0;
	return (new_map);
}

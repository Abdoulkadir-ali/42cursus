/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:18:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_index	find_cache_idx(t_scene *scene, const char *path)
{
	size_t	i;

	if (!path)
		return (index_error());
	i = 0;
	while (i < scene->cache_count)
	{
		if (ft_strcmp(scene->cache[i].path, path) == 0)
			return (index_success(i));
		i++;
	}
	return (index_error());
}

/**
 * Checks if a model for a given path already exists in the cache.
 */
bool	mesh_cache_has(t_scene *scene, const char *path)
{
	return (!find_cache_idx(scene, path).error);
}

t_model_cache	*get_cache_entry(t_scene *scene, size_t idx)
{
	if (idx >= scene->cache_count)
		return (NULL);
	return (&scene->cache[idx]);
}

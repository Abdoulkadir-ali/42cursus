/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:07:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

int	find_cache_idx(t_scene *scene, const char *path)
{
	int	i;

	if (!path)
	{
		if (scene->cache_count >= MAX_MODEL_CACHE)
			return (-2);
		return (-1);
	}
	i = 0;
	while (i < scene->cache_count)
	{
		if (ft_strcmp(scene->cache[i].path, path) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_model_cache	*get_cache_entry(t_scene *scene, int idx)
{
	if (idx == -2)
	{
		scene->cache_count++;
		return (&scene->cache[scene->cache_count - 1]);
	}
	if (idx < 0 || idx >= scene->cache_count)
		return (NULL);
	return (&scene->cache[idx]);
}

bool	mesh_cache_has(t_scene *scene, const char *path)
{
	return (find_cache_idx(scene, path) >= 0);
}

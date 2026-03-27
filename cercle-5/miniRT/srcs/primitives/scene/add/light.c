/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 05:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Ensures light pool capacity.
 */
static bool	ensure_light_cap(t_scene *scene)
{
	t_light	*new_lights;
	size_t	new_cap;

	if (scene->light_count < scene->light_cap)
		return (true);
	new_cap = scene->light_cap;
	if (new_cap == 0)
		new_cap = 16;
	else
		new_cap *= 2;
	new_lights = ft_realloc(scene->lights, scene->light_count * sizeof(t_light), 
				new_cap * sizeof(t_light));
	if (!new_lights)
		return (false);
	scene->lights = new_lights;
	scene->light_cap = new_cap;
	return (true);
}

/**
 * @brief Public bridge for adding lights to the scene pool.
 */
bool	scene_add_light(t_scene *scene, t_light light)
{
	if (!ensure_light_cap(scene))
		return (false);
	scene->lights[scene->light_count++] = light;
	return (true);
}

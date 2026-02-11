/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Adds a light to the scene.
*/
bool	scene_add_light(t_scene *scene, t_light light)
{
	if (!DYNARRAY_ENSURE_INT(&scene->lights, &scene->light_count,
			&scene->light_cap, sizeof(t_light)))
		return (false);
	scene->lights[scene->light_count++] = light;
	return (true);
}

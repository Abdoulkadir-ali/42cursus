/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:21:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_capsule(t_scene *scene, t_capsule cap)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, cap.temp_color);
	if (mat_id.error)
		return (false);
	cap.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->capsules, &scene->capsule_count,
			&scene->capsule_cap, sizeof(t_capsule)))
		return (false);
	scene->capsules[scene->capsule_count++] = cap;
	return (true);
}

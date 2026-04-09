/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Adds a cone to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cone(t_scene *scene, t_cone cone)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, cone.temp_color);
	if (mat_id.error)
		return (false);
	cone.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->cones, &scene->cone_count,
			&scene->cone_cap, sizeof(t_cone)))
		return (false);
	cone.mat_slots[0] = cone.mat_id;
	cone.mat_slots[1] = scene->mat_slot_checker;
	cone.mat_slots[2] = scene->mat_slot_solid;
	cone.mat_slots[3] = 0;
	cone.active_slot = 0;
	if (vec3_mag_sq(cone.transform.scale) < 1e-6)
		cone.transform.scale = vec3(1, 1, 1);
	scene->cones[scene->cone_count++] = cone;
	return (true);
}

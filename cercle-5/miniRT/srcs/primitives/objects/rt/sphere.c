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
** Adds a sphere to the scene.
*/
bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id.error)
		return (false);
	sphere.mat_id = mat_id.i;
	if (scene_allocate_object_slot((void **)&scene->spheres,
			&scene->sphere_count, &scene->sphere_cap, sizeof(t_sphere)).error)
		return (false);
sphere.mat_slots[0] = sphere.mat_id;
sphere.mat_slots[1] = scene->mat_slot_checker;
sphere.mat_slots[2] = scene->mat_slot_solid;
sphere.mat_slots[3] = 0;
sphere.active_slot = 0;
	if (vec3_mag_sq(sphere.transform.scale) < 1e-6)
		sphere.transform.scale = vec3(1, 1, 1);
	scene->spheres[scene->sphere_count - 1] = sphere;
	return (true);
}

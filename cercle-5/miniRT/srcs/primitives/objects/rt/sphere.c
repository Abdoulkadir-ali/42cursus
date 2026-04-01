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
	int	mat_id;

	mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id < 0)
		return (false);
	sphere.mat_id = mat_id;
	if (scene_allocate_object_slot((void **)&scene->spheres,
			&scene->sphere_count, &scene->sphere_cap, sizeof(t_sphere)) < 0)
		return (false);
	if (vec3_mag_sq(sphere.transform.scale) < 1e-6)
		sphere.transform.scale = vec3(1, 1, 1);
	scene->spheres[scene->sphere_count - 1] = sphere;
	return (true);
}

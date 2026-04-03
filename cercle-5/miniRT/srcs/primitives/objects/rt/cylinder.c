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
** Adds a cylinder to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, cylinder.temp_color);
	if (mat_id.error)
		return (false);
	cylinder.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->cylinders, &scene->cylinder_count,
			&scene->cylinder_cap, sizeof(t_cylinder)))
		return (false);
	if (vec3_mag_sq(cylinder.transform.scale) < 1e-6)
		cylinder.transform.scale = vec3(1, 1, 1);
	scene->cylinders[scene->cylinder_count++] = cylinder;
	return (true);
}

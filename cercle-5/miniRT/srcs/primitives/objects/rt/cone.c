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
	int	mat_id;

	mat_id = scene_add_material(scene, cone.temp_color);
	if (mat_id < 0)
		return (false);
	cone.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->cones, &scene->cone_count,
			&scene->cone_cap, sizeof(t_cone)))
		return (false);
	if (vec3_mag_sq(cone.transform.scale) < 1e-6)
		cone.transform.scale = vec3(1, 1, 1);
	scene->cones[scene->cone_count++] = cone;
	return (true);
}

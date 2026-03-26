/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	int	mat_id;

	mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id < 0)
		return (false);
	sphere.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->spheres, &scene->sphere_count,
			&scene->sphere_cap, sizeof(t_sphere)))
		return (false);
	if (vec3_mag_sq(sphere.transform.scale) < SCALE_EPSILON)
		sphere.transform.scale = vec3(1, 1, 1);
	scene->spheres[scene->sphere_count++] = sphere;
	return (true);
}

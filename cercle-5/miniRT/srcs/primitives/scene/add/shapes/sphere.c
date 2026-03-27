/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 13:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	if (!DYNARRAY_ENSURE_INT(&scene->spheres, &scene->sphere_count,
			&scene->sphere_cap, sizeof(t_sphere)))
		return (false);
	if (vec3_mag_sq(sphere.transform.scale) < SCALE_EPSILON)
		sphere.transform.scale = vec3(1, 1, 1);
	scene->spheres[scene->sphere_count++] = sphere;
	return (true);
}

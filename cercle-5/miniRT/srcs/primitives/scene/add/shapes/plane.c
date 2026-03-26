/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_plane(t_scene *scene, t_plane plane)
{
	int	mat_id;

	mat_id = scene_add_material(scene, plane.temp_color);
	if (mat_id < 0)
		return (false);
	plane.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->planes, &scene->plane_count,
			&scene->plane_cap, sizeof(t_plane)))
		return (false);
	if (vec3_mag_sq(plane.transform.scale) < SCALE_EPSILON)
		plane.transform.scale = vec3(1, 1, 1);
	scene->planes[scene->plane_count++] = plane;
	return (true);
}

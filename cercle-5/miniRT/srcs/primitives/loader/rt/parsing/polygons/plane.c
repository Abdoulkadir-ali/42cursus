/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_plane(t_scene *scene, t_plane plane)
{
	if (!DYNARRAY_ENSURE_INT(&scene->planes, &scene->plane_count,
			&scene->plane_cap, sizeof(t_plane)))
		return (false);
	if (vec3_mag_sq(plane.transform.scale) < SCALE_EPSILON)
		plane.transform.scale = vec3(1, 1, 1);
	scene->planes[scene->plane_count++] = plane;
	return (true);
}

bool	parse_plane(t_scene *scene, t_parser *p)
{
	t_plane	plane;
	t_vec3	color;

	ft_memset(&plane, 0, sizeof(t_plane));
	if (!parse_vec3(p, &plane.transform.pos))
		return (false);
	if (!parse_vec3(p, &plane.normal))
		return (false);
	if (!parse_vec3(p, &color))
		return (false);
	plane.normal = vec3_norm(plane.normal);
	plane.mat_id = scene_add_material(scene, color);
	if (plane.mat_id < 0)
		return (false);
	return (scene_add_plane(scene, plane));
}

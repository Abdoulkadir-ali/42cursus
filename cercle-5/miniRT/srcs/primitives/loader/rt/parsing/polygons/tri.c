/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:22:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_tri(t_scene *scene, t_tri_shape tri)
{
	if (!DYNARRAY_ENSURE_INT(&scene->tris, &scene->tri_count,
			&scene->tri_cap, sizeof(t_tri_shape)))
		return (false);
	if (vec3_mag_sq(tri.transform.scale) < SCALE_EPSILON)
		tri.transform.scale = vec3(1, 1, 1);
	scene->tris[scene->tri_count++] = tri;
	return (true);
}

bool	parse_tri_shape(t_scene *scene, t_parser *p)
{
	t_tri_shape	tri;
	t_vec3		color;
	t_vec3		e1;
	t_vec3		e2;

	ft_memset(&tri, 0, sizeof(t_tri_shape));
	if (!parse_vec3(p, &tri.v[0]) || !parse_vec3(p, &tri.v[1])
		|| !parse_vec3(p, &tri.v[2]) || !parse_vec3(p, &color))
		return (false);
	e1 = vec3_sub(tri.v[1], tri.v[0]);
	e2 = vec3_sub(tri.v[2], tri.v[0]);
	/* Math is now part of the injection pipeline */
	tri.transform.pos = vec3_scale(vec3_add(vec3_add(tri.v[0], tri.v[1]),
				tri.v[2]), 1.0 / 3.0);
	tri.mat_id = scene_add_material(scene, color);
	if (tri.mat_id < 0)
		return (false);
	return (scene_add_tri(scene, tri));
}
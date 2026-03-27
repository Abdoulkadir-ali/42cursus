/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:18:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_capsule(t_scene *scene, t_capsule capsule)
{
	if (!DYNARRAY_ENSURE_INT(&scene->capsules, &scene->capsule_count,
			&scene->capsule_cap, sizeof(t_capsule)))
		return (false);
	if (vec3_mag_sq(capsule.transform.scale) < SCALE_EPSILON)
		capsule.transform.scale = vec3(1, 1, 1);
	scene->capsules[scene->capsule_count++] = capsule;
	return (true);
}

bool	parse_capsule(t_scene *scene, t_parser *p)
{
	t_capsule	cp;
	t_vec3		color;

	ft_memset(&cp, 0, sizeof(t_capsule));
	if (!parse_vec3(p, &cp.transform.pos))
		return (false);
	if (!parse_vec3(p, &cp.axis))
		return (false);
	cp.radius = parse_double(p);
	cp.half_height = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	cp.axis = vec3_norm(cp.axis);
	cp.mat_id = scene_add_material(scene, color);
	return (scene_add_capsule(scene, cp));
}

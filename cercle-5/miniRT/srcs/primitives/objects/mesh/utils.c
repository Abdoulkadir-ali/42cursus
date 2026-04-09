/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:07:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	t_mesh	*m;

	if (vec3_mag_sq(animated.base.transform.scale) < 1e-6)
		animated.base.transform.scale = vec3(1, 1, 1);
	if (!DYNARRAY_ENSURE_INT(&scene->animated, &scene->anim_count,
			&scene->anim_cap, sizeof(t_skinned_mesh)))
		return (false);
	scene->animated[scene->anim_count++] = animated;
	m = &scene->animated[scene->anim_count - 1].base;
	m->mat_slots[0] = m->mat_id;
	m->mat_slots[1] = scene->mat_slot_checker;
	m->mat_slots[2] = scene->mat_slot_solid;
	m->mat_slots[3] = 0;
	m->active_slot = 0;
	return (true);
}

bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	t_mesh	*m;

	if (!DYNARRAY_ENSURE_INT(&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	if (vec3_mag_sq(mesh.transform.scale) < 1e-6)
		mesh.transform.scale = vec3(1, 1, 1);
	scene->meshes[scene->mesh_count++] = mesh;
	m = &scene->meshes[scene->mesh_count - 1];
	m->mat_slots[0] = m->mat_id;
	m->mat_slots[1] = scene->mat_slot_checker;
	m->mat_slots[2] = scene->mat_slot_solid;
	m->mat_slots[3] = 0;
	m->active_slot = 0;
	return (true);
}

bool	scene_add_group(t_scene *scene, t_mesh_group g)
{
	if (!DYNARRAY_ENSURE_INT(&scene->groups, &scene->group_count,
			&scene->group_cap, sizeof(t_mesh_group)))
		return (false);
	scene->groups[scene->group_count++] = g;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:07:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_aabb	get_mesh_aabb(t_mesh *mesh)
{
	if (mesh->transform.pos.x == 0 && mesh->transform.pos.y == 0
		&& mesh->transform.pos.z == 0 && mesh->transform.rotation.pitch == 0
		&& mesh->transform.rotation.yaw == 0 && mesh->transform.scale.x == 1
		&& mesh->transform.scale.y == 1 && mesh->transform.scale.z == 1)
		return (mesh->bbox);
	return (aabb_transform(mesh->bbox, mesh->transform));
}

/**
 * Generates a world-space AABB from a scene object reference.
 */
t_aabb	aabb_from_ref(t_scene *scene, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE)
		return (sphere_aabb(&scene->spheres[ref.index]));
	if (ref.type == TYPE_PLANE)
		return (plane_aabb(&scene->planes[ref.index]));
	if (ref.type == TYPE_CYLINDER)
		return (cylinder_aabb(&scene->cylinders[ref.index]));
	if (ref.type == TYPE_CONE)
		return (cone_aabb(&scene->cones[ref.index]));
	if (ref.type == TYPE_MESH)
		return (get_mesh_aabb(&scene->meshes[ref.index]));
	return (aabb_create_empty());
}

// static t_aabb	get_anim_aabb(t_anim *anim)
// {
// 	return (aabb_transform(anim->base.bbox, anim->base.transform));
// }

// t_aabb	aabb_from_ref(t_scene *scene, t_bvh_ref ref)
// {
// 	if (ref.type == TYPE_SPHERE)
// 		return (sphere_aabb(&scene->spheres[ref.index]));
// 	if (ref.type == TYPE_PLANE)
// 		return (plane_aabb(&scene->planes[ref.index]));
// 	if (ref.type == TYPE_CYLINDER)
// 		return (cylinder_aabb(&scene->cylinders[ref.index]));
// 	if (ref.type == TYPE_CONE)
// 		return (cone_aabb(&scene->cones[ref.index]));
// 	if (ref.type == TYPE_MESH)
// 		return (get_mesh_aabb(&scene->meshes[ref.index]));
// 	if (ref.type == TYPE_ANIM)
// 		return (get_anim_aabb(&scene->animated[ref.index]));
// 	return (aabb_create_empty());
// }
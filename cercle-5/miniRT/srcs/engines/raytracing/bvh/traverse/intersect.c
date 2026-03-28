/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD-compliant intersection dispatcher using Unified Primitive Array (SoA).
 * Routes ray tests to specialized batch-friendly functions without legacy indirection.
 */
static bool	dispatch_intersect(const t_ray *ray, t_scene *scene,
		t_bvh_ref ref, t_hit *hit)
{
	t_primitive_array	*p;


	p = &scene->primitives;

	if (ref.type == TYPE_TRI)
		return (intersect_tri_soa(ray, &scene->tri_soa, ref.index, hit));
	if (ref.type == TYPE_SPHERE)
		return (intersect_sphere(ray, p, ref.index, hit));
	if (ref.type == TYPE_PLANE)
		return (intersect_plane(ray, p, ref.index, hit));
	if (ref.type == TYPE_CYLINDER)
		return (intersect_cylinder(ray, p, ref.index, hit));
	if (ref.type == TYPE_CONE)
		return (intersect_cone(ray, p, ref.index, hit));
	if (ref.type == TYPE_RECT)
		return (intersect_rect(ray, p, ref.index, hit));
	if (ref.type == TYPE_BOX)
		return (intersect_box(ray, p, ref.index, hit));
	if (ref.type == TYPE_CAPSULE)
		return (intersect_capsule(ray, p, ref.index, hit));
	if (ref.type == TYPE_PYRAMID)
		return (intersect_pyramid(ray, p, ref.index, hit));
	return (false);
}

bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
	t_hit *hit)
{
	if (!dispatch_intersect(ray, scene, ref, hit))
		return (false);
	hit->ref = ref;
	hit->type = ref.type;
	return (true);
}

/**
 * @brief Principal entry point for the bounding volume hierarchy (BVH) ray traversal loop.
 */
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || bvh->num_nodes == 0)
		return (false);
	hit->t = MAX_VALUE;
	hit->ref.type = TYPE_NONE;
	return (run_traverse_loop(bvh, ray, hit));
}
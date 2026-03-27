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
	int					i;

	p = &scene->primitives;
	i = ref.index;
	if (ref.type == TYPE_TRI)
		return (intersect_tri_soa(ray, &scene->tri_soa, i, hit));
	if (ref.type == PRIM_SPHERE)
		return (intersect_sphere(ray, p, i, hit));
	if (ref.type == PRIM_PLANE)
		return (intersect_plane(ray, p, i, hit));
	if (ref.type == PRIM_CYLINDER)
		return (intersect_cylinder(ray, p, i, hit));
	if (ref.type == PRIM_CONE)
		return (intersect_cone(ray, p, i, hit));
	/* Rect/Box/Capsule etc will use the same pattern */
	return (false);
}

bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		 t_hit *hit)
{
	bool	res;

	res = dispatch_intersect(ray, scene, ref, hit);
	if (res)
		hit->ref = ref;
	return (res);
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
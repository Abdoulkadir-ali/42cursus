/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlude.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:45:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Fast sphere occlusion bypassing exhaustive tangent checking logic.
 * 
 * Provides an accelerated verification simply solving the quadratic representation
 * equation without bothering to generate fully-formatted hits (UV/Tangents). It is highly optimized
 * solely to return true if shadows apply across the interval.
 * 
 * @param ray   Pointer directly tracking projection origin parameters.
 * @param sp    Mutable pointer referencing sphere configuration matrix and metrics.
 * @param max_t A limit ensuring light sources beyond geometric spheres don't falsely occlude.
 * 
 * @return Returns `true` representing an occlusion occurring on the shadow path. `false` on clear sight.
 */
static bool	occlude_sphere(const t_ray *ray, t_sphere *sp, double max_t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	disc;
	double	t;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	disc = b * b - 4.0 * a * (vec3_dot(oc, oc) - sp->radius_sq);
	if (disc < 0.0)
		return (false);
	disc = sqrt(disc);
	t = (-b - disc) / (2.0 * a);
	if (t < EPSILON)
		t = (-b + disc) / (2.0 * a);
	return (t > EPSILON && t < max_t);
}

/**
 * @brief Verifies geometry obstruction specifically utilizing simplified collision tests.
 * 
 * Invokes native shapes' optimized unblocking evaluation routines. For elements
 * lacking customized routines like spheres, this elegantly defaults checking utilizing
 * standard `intersect_object` methodologies. Non-static intentionally to integrate with BVH splits.
 * 
 * @param ray   Incoming projected light mapping or shadow traversal segments.
 * @param scene Complete state of properties comprising background environment buffers.
 * @param ref   Extracted metadata isolating primitive classes for precise evaluations.
 * @param max_t Floating point bounding limitations restricting test depth.
 * 
 * @return True confirms the primitive explicitly blocks the path inside boundary constraints. Otherwise false.
 */
bool	occlude_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		double max_t)
{
	t_hit	temp;

	if (ref.type == TYPE_SPHERE)
		return (occlude_sphere(ray, &scene->spheres[ref.index], max_t));
	temp.t = max_t;
	if (intersect_object(ray, scene, ref, &temp))
		return (temp.t > EPSILON && temp.t < max_t);
	return (false);
}

/**
 * @brief Determines if an unobstructed path exists over a specific distance by dispatching an occluded ray traversal.
 * 
 * Designed heavily for fast shadow-ray optimization, eliminating full hit records
 * computation. If the initial root bounding box reveals an imminent miss, the routine
 * stops early preventing the costly walk through the sub-branches and leaves.
 * 
 * @param bvh   A constant pointer to the scene's BVH tree data.
 * @param ray   A constant pointer to the traversal ray (e.g., origin point mapping towards the light source).
 * @param max_t The maximum tested travel distance against any geometry checking occlusion (distance to light).
 * 
 * @return Returns `true` if an object occludes the path ahead of `max_t`. `false` if totally unoccluded.
 */
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	double	min;
	double	max;

	if (!bvh || bvh->num_nodes == 0)
		return (false);
	min = 0.0;
	max = MAX_VALUE;
	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &min, &max))
		return (false);
	return (bvh_traverse_loop(bvh, ray, max_t));
}

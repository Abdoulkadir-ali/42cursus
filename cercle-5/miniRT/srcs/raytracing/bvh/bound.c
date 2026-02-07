/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 01:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "scene.h"
#include <math.h>

static t_aabb	sphere_aabb(t_sphere *sp)
{
	t_aabb	bbox;
	double	r;

	r = sqrt(sp->radius_sq);
	bbox.min = vec3_sub(sp->pos, vec3(r, r, r));
	bbox.max = vec3_add(sp->pos, vec3(r, r, r));
	return (bbox);
}

static t_aabb	plane_aabb(t_plane *pl)
{
	t_aabb	bbox;

	(void)pl;
	// Planes are infinite, but for BVH we usually don't bound them or use a huge box
	// However, if we put them in a BVH, they need some bounds.
	// For miniRT, often planes are treated as "infinite background" and might 
	// stay outside the BVH, or have massive bounds.
	bbox.min = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	bbox.max = vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	return (bbox);
}

static t_aabb	cylinder_aabb(t_cylinder *cy)
{
	t_aabb	bbox;
	double	r = cy->radius;
	double	h = cy->height;

	// Simplistic axis-aligned bounding box for cylinder (assumes axis aligned for now, 
	// or just a conservative box)
	// Real bounding box would involve the axis rotation.
	bbox.min = vec3_sub(cy->pos, vec3(r, h, r));
	bbox.max = vec3_add(cy->pos, vec3(r, h, r));
	return (bbox);
}

t_aabb	aabb_from_ref(t_scene *scene, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE)
		return (sphere_aabb(&scene->spheres[ref.index]));
	if (ref.type == TYPE_PLANE)
		return (plane_aabb(&scene->planes[ref.index]));
	if (ref.type == TYPE_CYLINDER)
		return (cylinder_aabb(&scene->cylinders[ref.index]));
	if (ref.type == TYPE_MESH)
		return (scene->meshes[ref.index].bbox);
	if (ref.type == TYPE_ANIM)
		return (scene->animated[ref.index].base.bbox);
	return ((t_aabb){vec3(0, 0, 0), vec3(0, 0, 0)});
}

t_aabb	aabb_create_empty(void)
{
	t_aabb	bbox;

	bbox.min = vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	bbox.max = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	return (bbox);
}

t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	bbox;

	bbox.min = vec3(
		fmin(a->min.x, b->min.x),
		fmin(a->min.y, b->min.y),
		fmin(a->min.z, b->min.z)
	);
	bbox.max = vec3(
		fmax(a->max.x, b->max.x),
		fmax(a->max.y, b->max.y),
		fmax(a->max.z, b->max.z)
	);
	return (bbox);
}

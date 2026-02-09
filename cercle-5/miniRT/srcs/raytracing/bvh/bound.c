/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:40:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a sphere.
 */
static t_aabb	sphere_aabb(t_sphere *sp)
{
	t_aabb	bbox;
	double	r;

	r = sqrt(sp->radius_sq);
	bbox.min = vec3_sub(sp->transform.pos, vec3(r, r, r));
	bbox.max = vec3_add(sp->transform.pos, vec3(r, r, r));
	return (bbox);
}

/**
 * Computes the Axis-Aligned Bounding Box for a plane (infinite).
 */
static t_aabb	plane_aabb(t_plane *pl)
{
	t_aabb	bbox;

	(void)pl;
	bbox.min = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	bbox.max = vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	return (bbox);
}

/**
 * Computes the Axis-Aligned Bounding Box for a cylinder.
 */
static t_aabb	cylinder_aabb(t_cylinder *cy)
{
	t_aabb	bbox;
	double	r;
	double	h;

	r = cy->transform.scale.x;
	h = cy->transform.scale.y;
	bbox.min = vec3_sub(cy->transform.pos, vec3(r, h, r));
	bbox.max = vec3_add(cy->transform.pos, vec3(r, h, r));
	return (bbox);
}

/**
 * Computes the Axis-Aligned Bounding Box for a cone.
 */
static t_aabb	cone_aabb(t_cone *co)
{
	t_aabb	bbox;
	double	r;
	double	h;

	r = co->transform.scale.x;
	h = co->transform.scale.y;
	bbox.min = vec3_sub(co->transform.pos, vec3(r, h, r));
	bbox.max = vec3_add(co->transform.pos, vec3(r, h, r));
	return (bbox);
}

/**
 * Transforms a local AABB into world space by applying the object's transform.
 * For now, only handles translation and uniform scale.
 */
static t_aabb	transform_aabb(t_aabb local, t_transform t)
{
	t_aabb	w;
	t_vec3	c[8];
	int		i;

	c[0] = vec3_add(vec3_mul(vec3(local.min.x, local.min.y, local.min.z), \
		t.scale), t.pos);
	c[1] = vec3_add(vec3_mul(vec3(local.max.x, local.min.y, local.min.z), \
		t.scale), t.pos);
	c[2] = vec3_add(vec3_mul(vec3(local.min.x, local.max.y, local.min.z), \
		t.scale), t.pos);
	c[3] = vec3_add(vec3_mul(vec3(local.max.x, local.max.y, local.min.z), \
		t.scale), t.pos);
	c[4] = vec3_add(vec3_mul(vec3(local.min.x, local.min.y, local.max.z), \
		t.scale), t.pos);
	c[5] = vec3_add(vec3_mul(vec3(local.max.x, local.min.y, local.max.z), \
		t.scale), t.pos);
	c[6] = vec3_add(vec3_mul(vec3(local.min.x, local.max.y, local.max.z), \
		t.scale), t.pos);
	c[7] = vec3_add(vec3_mul(vec3(local.max.x, local.max.y, local.max.z), \
		t.scale), t.pos);
	w.min = vec3(1e30, 1e30, 1e30);
	w.max = vec3(-1e30, -1e30, -1e30);
	i = -1;
	while (++i < 8)
	{
		w.min.x = fmin(w.min.x, c[i].x);
		w.min.y = fmin(w.min.y, c[i].y);
		w.min.z = fmin(w.min.z, c[i].z);
		w.max.x = fmax(w.max.x, c[i].x);
		w.max.y = fmax(w.max.y, c[i].y);
		w.max.z = fmax(w.max.z, c[i].z);
	}
	return (w);
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
		return (transform_aabb(scene->meshes[ref.index].bbox, \
			scene->meshes[ref.index].transform));
	if (ref.type == TYPE_ANIM)
		return (transform_aabb(scene->animated[ref.index].base.bbox, \
			scene->animated[ref.index].base.transform));
	return ((t_aabb){vec3(0, 0, 0), vec3(0, 0, 0)});
}

/**
 * Creates an empty AABB with inverse-infinite bounds.
 */
t_aabb	aabb_create_empty(void)
{
	t_aabb	bbox;

	bbox.min = vec3(DBL_MAX, DBL_MAX, DBL_MAX);
	bbox.max = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	return (bbox);
}

/**
 * Computes the union of two Axis-Aligned Bounding Boxes.
 */
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	bbox;

	bbox.min = vec3(fmin(a->min.x, b->min.x), fmin(a->min.y, b->min.y), \
		fmin(a->min.z, b->min.z));
	bbox.max = vec3(fmax(a->max.x, b->max.x), fmax(a->max.y, b->max.y), \
		fmax(a->max.z, b->max.z));
	return (bbox);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:05:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 06:05:25 by abdoali          ###   ########.fr       */
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
	bbox.min = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	bbox.max = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
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
 * Handles translation, rotation, and scaling.
 */
t_aabb	aabb_transform(t_aabb local, t_transform t)
{
	t_aabb	w;
	t_vec3	c[8];
	t_mat4	m;
	int		i;
	t_vec3	v;

	m = mat4_transform(t);
	c[0] = local.min;
	c[1] = vec3(local.min.x, local.min.y, local.max.z);
	c[2] = vec3(local.min.x, local.max.y, local.min.z);
	c[3] = vec3(local.min.x, local.max.y, local.max.z);
	c[4] = vec3(local.max.x, local.min.y, local.min.z);
	c[5] = vec3(local.max.x, local.min.y, local.max.z);
	c[6] = vec3(local.max.x, local.max.y, local.min.z);
	c[7] = local.max;
	w.min = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
	w.max = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	i = -1;
	while (++i < 8)
	{
		v = mat4_mul_pos(m, c[i]);
		w.min.x = fmin(w.min.x, v.x);
		w.min.y = fmin(w.min.y, v.y);
		w.min.z = fmin(w.min.z, v.z);
		w.max.x = fmax(w.max.x, v.x);
		w.max.y = fmax(w.max.y, v.y);
		w.max.z = fmax(w.max.z, v.z);
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
	/* Optimization: P5 - Check for identity transform */
	if (ref.type == TYPE_MESH)
	{
		if (scene->meshes[ref.index].transform.pos.x == 0
			&& scene->meshes[ref.index].transform.pos.y == 0
			&& scene->meshes[ref.index].transform.pos.z == 0
			&& scene->meshes[ref.index].transform.rotation.pitch == 0
			&& scene->meshes[ref.index].transform.rotation.yaw == 0
			&& scene->meshes[ref.index].transform.scale.x == 1
			&& scene->meshes[ref.index].transform.scale.y == 1
			&& scene->meshes[ref.index].transform.scale.z == 1)
			return (scene->meshes[ref.index].bbox);
		return (aabb_transform(scene->meshes[ref.index].bbox,
				scene->meshes[ref.index].transform));
	}
	if (ref.type == TYPE_ANIM)
		return (aabb_transform(scene->animated[ref.index].base.bbox,
				scene->animated[ref.index].base.transform));
	return (aabb_create_empty());
}

/**
 * Creates an empty AABB with inverse-infinite bounds.
 */
t_aabb	aabb_create_empty(void)
{
	t_aabb	bbox;

	bbox.min = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
	bbox.max = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	return (bbox);
}

/**
 * Computes the union of two Axis-Aligned Bounding Boxes.
 */
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	bbox;

	bbox.min = vec3(fmin(a->min.x, b->min.x), fmin(a->min.y, b->min.y),
			fmin(a->min.z, b->min.z));
	bbox.max = vec3(fmax(a->max.x, b->max.x), fmax(a->max.y, b->max.y),
			fmax(a->max.z, b->max.z));
	return (bbox);
}

/**
 * Expands an AABB to include a point.
 */
void	aabb_expand_point(t_aabb *bbox, t_vec3 p)
{
	bbox->min.x = fmin(bbox->min.x, p.x);
	bbox->min.y = fmin(bbox->min.y, p.y);
	bbox->min.z = fmin(bbox->min.z, p.z);
	bbox->max.x = fmax(bbox->max.x, p.x);
	bbox->max.y = fmax(bbox->max.y, p.y);
	bbox->max.z = fmax(bbox->max.z, p.z);
}

/**
 * Computes the surface area of an Axis-Aligned Bounding Box.
 */
double	aabb_surface_area(t_aabb bbox)
{
	t_vec3	d;

	d = vec3_sub(bbox.max, bbox.min);
	if (d.x < 0 || d.y < 0 || d.z < 0)
		return (0);
	return (2 * (d.x * d.y + d.y * d.z + d.z * d.x));
}

/**
 * Fast AABB intersection test using the slabs method.
 */
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax)
{
	double	t1;
	double	t2;

	t1 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t2 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	*tmin = fmin(t1, t2);
	*tmax = fmax(t1, t2);
	t1 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t2 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	*tmin = fmax(*tmin, fmin(t1, t2));
	*tmax = fmin(*tmax, fmax(t1, t2));
	t1 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t2 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	*tmin = fmax(*tmin, fmin(t1, t2));
	*tmax = fmin(*tmax, fmax(t1, t2));
	return (*tmax >= 0 && *tmax >= *tmin);
}

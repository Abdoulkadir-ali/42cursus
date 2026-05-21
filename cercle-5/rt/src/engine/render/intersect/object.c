/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"


t_aabb	object_bounds(const t_object *o)
{
	if (o->type == OBJ_SPHERE)
		return (sphere_bounds(&o->u.sph));
	if (o->type == OBJ_CYLINDER)
		return (cylinder_bounds(&o->u.cyl));
	if (o->type == OBJ_BOX)
		return (box_bounds(&o->u.box));
	if (o->type == OBJ_CAPSULE)
		return (capsule_bounds(&o->u.cap));
	if (o->type == OBJ_PYRAMID)
		return (pyramid_bounds(&o->u.pyr));
	if (o->type == OBJ_TRIANGLE)
		return (triangle_bounds(&o->u.tri));
	return ((t_aabb){v3(-1e6, -1e6, -1e6), v3(1e6, 1e6, 1e6)});
}


t_vec3	object_center(const t_object *o)
{
	t_vec3	c;

	if (o->type == OBJ_SPHERE)
		return (o->u.sph.center);
	if (o->type == OBJ_PLANE)
		return (o->u.pln.point);
	if (o->type == OBJ_CYLINDER)
		return (v3_add(o->u.cyl.base,
			v3_mul(o->u.cyl.axis, o->u.cyl.height * 0.5f)));
	if (o->type == OBJ_BOX)
		return (o->u.box.center);
	if (o->type == OBJ_CAPSULE)
		return (v3_add(o->u.cap.base,
			v3_mul(o->u.cap.axis, o->u.cap.height * 0.5f)));
	if (o->type == OBJ_PYRAMID)
		return (v3_add(o->u.pyr.base,
			v3_mul(o->u.pyr.axis, o->u.pyr.height * 0.5f)));
	c = v3_add(v3_add(o->u.tri.a, o->u.tri.b), o->u.tri.c);
	return (v3_mul(c, 1.0f / 3.0f));
}


float	object_bsphere_radius(const t_object *o)
{
	if (o->type == OBJ_SPHERE)
		return (o->u.sph.radius);
	if (o->type == OBJ_CYLINDER)
		return (sqrtf(o->u.cyl.radius2
			+ o->u.cyl.height * o->u.cyl.height * 0.25f));
	if (o->type == OBJ_BOX)
		return (v3_len(o->u.box.he));
	if (o->type == OBJ_CAPSULE)
		return (o->u.cap.radius + o->u.cap.height * 0.5f);
	if (o->type == OBJ_PYRAMID)
		return (sqrtf(o->u.pyr.side * o->u.pyr.side * 0.5f
			+ o->u.pyr.height * o->u.pyr.height) * 0.5f);
	if (o->type == OBJ_TRIANGLE)
	{
		t_vec3	c;
		float	r2;
		float	d;

		c = v3_mul(v3_add(v3_add(o->u.tri.a, o->u.tri.b), o->u.tri.c),
			1.0f / 3.0f);
		r2 = v3_dot(v3_sub(o->u.tri.a, c), v3_sub(o->u.tri.a, c));
		d = v3_dot(v3_sub(o->u.tri.b, c), v3_sub(o->u.tri.b, c));
		if (d > r2)
			r2 = d;
		d = v3_dot(v3_sub(o->u.tri.c, c), v3_sub(o->u.tri.c, c));
		if (d > r2)
			r2 = d;
		return (sqrtf(r2));
	}
	return (1.0f);
}


void	object_translate_to(t_object *o, t_vec3 newcenter)
{
	t_vec3	delta;

	delta = v3_sub(newcenter, object_center(o));
	if (o->type == OBJ_SPHERE)
		o->u.sph.center = newcenter;
	else if (o->type == OBJ_PLANE)
		o->u.pln.point = newcenter;
	else if (o->type == OBJ_CYLINDER)
		o->u.cyl.base = v3_add(o->u.cyl.base, delta);
	else if (o->type == OBJ_BOX)
		o->u.box.center = newcenter;
	else if (o->type == OBJ_CAPSULE)
		o->u.cap.base = v3_add(o->u.cap.base, delta);
	else if (o->type == OBJ_PYRAMID)
	{
		o->u.pyr.base = v3_add(o->u.pyr.base, delta);
		o->u.pyr.apex = v3_add(o->u.pyr.apex, delta);
	}
	else if (o->type == OBJ_TRIANGLE)
	{
		o->u.tri.a = v3_add(o->u.tri.a, delta);
		o->u.tri.b = v3_add(o->u.tri.b, delta);
		o->u.tri.c = v3_add(o->u.tri.c, delta);
	}
}


void	object_uv(const t_object *o, t_vec3 p, float *u, float *v)
{
	t_vec3	d;

	if (o->type == OBJ_SPHERE)
		return (sphere_uv(&o->u.sph, p, u, v));
	if (o->type == OBJ_PLANE)
		return (plane_uv(&o->u.pln, p, u, v));
	if (o->type == OBJ_CYLINDER)
		return (cylinder_uv(&o->u.cyl, p, u, v));
	if (o->type == OBJ_BOX)
	{
		d = v3_sub(p, o->u.box.center);
		*u = v3_dot(d, o->u.box.u) / (2.0f * o->u.box.he.x) + 0.5f;
		*v = v3_dot(d, o->u.box.v) / (2.0f * o->u.box.he.y) + 0.5f;
		return ;
	}
	*u = 0.0f;
	*v = 0.0f;
}

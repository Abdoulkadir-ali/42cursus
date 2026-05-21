/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:19:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	box_center(t_aabb b)
{
	return (v3_mul(v3_add(b.min, b.max), 0.5f));
}

t_aabb	obj_box(const t_object *o)
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
	return (triangle_bounds(&o->u.tri));
}

t_vec3	obj_center(const t_object *o)
{
	return (box_center(obj_box(o)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 01:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_aabb	sphere_aabb(t_sphere *sp)
{
	t_aabb	bbox;

	bbox.min = vec3_sub(sp->transform.pos, vec3(sp->radius, sp->radius, sp->radius));
	bbox.max = vec3_add(sp->transform.pos, vec3(sp->radius, sp->radius, sp->radius));
	return (bbox);
}

t_aabb	plane_aabb(t_plane *pl)
{
	t_aabb	bbox;

	bbox.min = vec3(-1e15, -1e15, -1e15);
	bbox.max = vec3(1e15, 1e15, 1e15);
	(void)pl;
	return (bbox);
}

t_aabb	cylinder_aabb(t_cylinder *cy)
{
	t_aabb	bbox;
	t_vec3	h_vec;

	h_vec = vec3(cy->radius, cy->height / 2.0, cy->radius);
	bbox.min = vec3_sub(cy->transform.pos, h_vec);
	bbox.max = vec3_add(cy->transform.pos, h_vec);
	return (aabb_transform(bbox, cy->transform));
}

t_aabb	cone_aabb(t_cone *co)
{
	t_aabb	bbox;
	t_vec3	h_v;

	h_v = vec3(co->radius, co->height / 2.0, co->radius);
	bbox.min = vec3_sub(co->transform.pos, h_v);
	bbox.max = vec3_add(co->transform.pos, h_v);
	return (aabb_transform(bbox, co->transform));
}

t_aabb	tri_aabb(t_tri_shape *tr)
{
	t_aabb	bbox;
	int		i;

	bbox = aabb_create_empty();
	i = -1;
	while (++i < 3)
		aabb_expand_point(&bbox, mat4_mul_pos(mat4_transform(tr->transform), tr->v[i]));
	return (bbox);
}

t_aabb	rect_aabb(t_rect *rc)
{
	t_aabb	bbox;
	int		i;

	bbox = aabb_create_empty();
	i = -1;
	while (++i < 4)
		aabb_expand_point(&bbox, mat4_mul_pos(mat4_transform(rc->transform), rc->v[i]));
	return (bbox);
}

t_aabb	pyramid_aabb(t_pyramid *py)
{
	t_aabb	bbox;
	int		i;

	bbox = aabb_create_empty();
	i = -1;
	while (++i < 5)
		aabb_expand_point(&bbox, mat4_mul_pos(mat4_transform(py->transform), py->v[i]));
	return (bbox);
}

t_aabb	box_aabb(t_box *bx)
{
	t_aabb	bbox;

	bbox.min = vec3_sub(bx->transform.pos, bx->half_extents);
	bbox.max = vec3_add(bx->transform.pos, bx->half_extents);
	return (aabb_transform(bbox, bx->transform));
}

t_aabb	capsule_aabb(t_capsule *cp)
{
	t_aabb	bbox;
	t_vec3	ext;

	ext = vec3(cp->radius, cp->half_height + cp->radius, cp->radius);
	bbox.min = vec3_sub(cp->transform.pos, ext);
	bbox.max = vec3_add(cp->transform.pos, ext);
	return (aabb_transform(bbox, cp->transform));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

static void	aabb_cyl_capsule(t_aabb *aabb, t_vec3 pos, t_vec3 axis, float h, float r)
{
	t_vec3	half;
	t_vec3	rad;

	half = vec3_scale(axis, h / 2.0f);
	rad = vec3(r, r, r);
	aabb->min = vec3_sub(vec3_sub(pos, half), rad);
	aabb->max = vec3_add(vec3_add(pos, half), rad);
}

static void	aabb_cone(t_aabb *aabb, t_vec3 pos, t_vec3 axis, float h, float r)
{
	t_vec3	half;
	t_vec3	rad;

	half = vec3_scale(axis, h / 2.0f);
	rad = vec3(r, r, r);
	aabb->min = vec3_sub(vec3_sub(pos, half), rad);
	aabb->max = vec3_add(vec3_add(pos, half), rad);
}

t_aabb	get_primitive_aabb_soa(t_primitive_array *p, int i)
{
	t_aabb	aabb;
	t_vec3	pos;
	t_vec3	axis;

	if (i < 0 || (size_t)i >= p->count)
		return (aabb_create_empty());
	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	if (p->types[i] == TYPE_SPHERE)
	{
		aabb.min = vec3_sub(pos, vec3(p->radii[i], p->radii[i], p->radii[i]));
		aabb.max = vec3_add(pos, vec3(p->radii[i], p->radii[i], p->radii[i]));
	}
	else if (p->types[i] == TYPE_PLANE)
	{
		aabb.min = vec3_sub(pos, vec3(1e6f, 1e6f, 1e6f));
		aabb.max = vec3_add(pos, vec3(1e6f, 1e6f, 1e6f));
	}
	else if (p->types[i] == TYPE_PYRAMID)
	{
		float r = p->radii[i];
		float h = p->heights[i];
		aabb.min = vec3(pos.x - r, pos.y, pos.z - r);
		aabb.max = vec3(pos.x + r, pos.y + h, pos.z + r);
	}
	else if (p->types[i] == TYPE_BOX)
	{
		aabb.min = vec3(pos.x - p->ex[i], pos.y - p->ey[i], pos.z - p->ez[i]);
		aabb.max = vec3(pos.x + p->ex[i], pos.y + p->ey[i], pos.z + p->ez[i]);
	}
	else if (p->types[i] == TYPE_CYLINDER || p->types[i] == TYPE_CAPSULE)
		aabb_cyl_capsule(&aabb, pos, axis, p->heights[i], p->radii[i]);
	else if (p->types[i] == TYPE_RECT)
	{
		aabb.min = vec3_sub(pos, vec3(p->ex[i], p->ey[i], 0.01f));
		aabb.max = vec3_add(pos, vec3(p->ex[i], p->ey[i], 0.01f));
	}
	else if (p->types[i] == TYPE_CONE)
		aabb_cone(&aabb, pos, axis, p->heights[i], p->radii[i]);
	else
		aabb = aabb_create_empty();
	return (aabb);
}

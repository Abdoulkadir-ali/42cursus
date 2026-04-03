/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:09:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:09:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_aabb	capsule_aabb(t_capsule *cap)
{
	t_aabb	aabb;
	t_vec3	p0;
	t_vec3	p1;

	p0 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	aabb = aabb_create_empty();
	aabb_expand_point(&aabb, p0);
	aabb_expand_point(&aabb, p1);
	aabb.min.x -= cap->radius;
	aabb.min.y -= cap->radius;
	aabb.min.z -= cap->radius;
	aabb.max.x += cap->radius;
	aabb.max.y += cap->radius;
	aabb.max.z += cap->radius;
	return (aabb);
}

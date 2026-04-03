/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:09:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	get_pyramid_corners(t_pyramid *py, t_vec3 corners[4])
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	corners[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	corners[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	corners[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	corners[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
}

/*
** Pyramid AABB: walk all 5 vertices (4 base corners + apex).
** Base corners are derived from center, up, base_size (as in the intersector).
*/
t_aabb	pyramid_aabb(t_pyramid *py)
{
	t_aabb	bb;
	t_vec3	corners[4];
	t_vec3	apex;
	size_t	i;

	get_pyramid_corners(py, corners);
	apex = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	bb.min = corners[0];
	bb.max = corners[0];
	i = 1;
	while (i < 4)
		aabb_expand_point(&bb, corners[i++]);
	aabb_expand_point(&bb, apex);
	bb.min = vec3_sub(bb.min, vec3(1e-4, 1e-4, 1e-4));
	bb.max = vec3_add(bb.max, vec3(1e-4, 1e-4, 1e-4));
	return (bb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:07:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	basis_from_up(t_vec3 up, t_vec3 *right, t_vec3 *fwd)
{
	t_vec3 ref;

	if (fabs(up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	*right = vec3_norm(vec3_cross(up, ref));
	*fwd = vec3_cross(*right, up);
}

static void	compute_corners(const t_pyramid *py, t_vec3 right,
				t_vec3 fwd, t_vec3 out[4])
{
	double h;

	h = py->base_size * 0.5;
	out[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	out[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	out[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	out[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
}

/* Public: compute pyramid axis-aligned bounding box */
t_aabb	pyramid_aabb(t_pyramid *py)
{
	t_aabb	bb;
	t_vec3	basis[2];
	t_vec3	corners[4];
	t_vec3	apex;
	int		i;

	basis_from_up(py->up, &basis[0], &basis[1]);
	compute_corners(py, basis[0], basis[1], corners);
	apex = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	bb = aabb_create_empty();
	i = -1;
	while (++i < 4)
		aabb_expand_point(&bb, corners[i]);
	aabb_expand_point(&bb, apex);
	aabb_expand_eps(&bb, 1e-4);
	return (bb);
}


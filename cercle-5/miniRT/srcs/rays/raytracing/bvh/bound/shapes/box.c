/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	get_box_axes(t_box *bx, t_vec3 ax[3])
{
	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		ax[0] = vec3(1, 0, 0);
	else
		ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
}

static t_vec3	get_box_corner(t_box *bx, t_vec3 ax[3], int i)
{
	t_vec3	s;

	s.x = (double)((i & 1) * 2 - 1);
	s.y = (double)(((i >> 1) & 1) * 2 - 1);
	s.z = (double)(((i >> 2) & 1) * 2 - 1);
	return (vec3_add(bx->transform.pos,
			vec3_add(vec3_scale(ax[0], s.x * bx->half_extents.x),
				vec3_add(vec3_scale(ax[1], s.y * bx->half_extents.y),
					vec3_scale(ax[2], s.z * bx->half_extents.z)))));
}

/**
 * @brief Computes the axis-aligned bounding box (AABB) for an oriented box.
 * Transforms all 8 corners and expands the AABB to encapsulate them.
 */
t_aabb	box_aabb(t_box *bx)
{
	t_aabb	aabb;
	t_vec3	ax[3];
	int		i;

	get_box_axes(bx, ax);
	aabb = aabb_create_empty();
	i = -1;
	while (++i < 8)
		aabb_expand_point(&aabb, get_box_corner(bx, ax, i));
	return (aabb);
}

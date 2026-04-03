/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:09:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:43:00 by abdoali          ###   ########.fr       */
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

t_aabb	box_aabb(t_box *bx)
{
	t_aabb	aabb;
	t_vec3	ax[3];
	t_vec3	c;
	t_vec3	s;
	size_t	i;

	get_box_axes(bx, ax);
	aabb = aabb_create_empty();
	i = 0;
	while (i < 8)
	{
		s.x = (double)((i & 1) * 2 - 1);
		s.y = (double)(((i >> 1) & 1) * 2 - 1);
		s.z = (double)(((i >> 2) & 1) * 2 - 1);
		c = vec3_add(bx->transform.pos,
				vec3_add(vec3_scale(ax[0], s.x * bx->half_extents.x),
					vec3_add(vec3_scale(ax[1], s.y * bx->half_extents.y),
						vec3_scale(ax[2], s.z * bx->half_extents.z))));
		aabb_expand_point(&aabb, c);
		i++;
	}
	return (aabb);
}

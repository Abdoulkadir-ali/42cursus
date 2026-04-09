/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:09:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 16:14:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_aabb	box_aabb(t_box *bx)
{
	t_aabb	aabb;
	t_vec3	c;
	t_vec3	s;
	size_t	i;

	aabb = aabb_create_empty();
	i = 0;
	while (i < 8)
	{
		s.x = (double)((i & 1) * 2 - 1);
		s.y = (double)(((i >> 1) & 1) * 2 - 1);
		s.z = (double)(((i >> 2) & 1) * 2 - 1);
		c = vec3_add(bx->phys.center,
				vec3_add(vec3_scale(bx->transform.forward, s.x * bx->half_extents.x),
					vec3_add(vec3_scale(bx->transform.right, s.y * bx->half_extents.y),
						vec3_scale(bx->transform.up, s.z * bx->half_extents.z))));
		aabb_expand_point(&aabb, c);
		i++;
	}
	return (aabb);
}

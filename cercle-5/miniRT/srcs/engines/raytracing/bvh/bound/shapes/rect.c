/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:09:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_aabb	rect_aabb(t_rect *rc)
{
	t_aabb	bbox;
	size_t	i;

	bbox.min = rc->v[0];
	bbox.max = rc->v[0];
	i = 1;
	while (i < 4)
		aabb_expand_point(&bbox, rc->v[i++]);
	bbox.min = vec3_sub(bbox.min, vec3(1e-4, 1e-4, 1e-4));
	bbox.max = vec3_add(bbox.max, vec3(1e-4, 1e-4, 1e-4));
	return (bbox);
}

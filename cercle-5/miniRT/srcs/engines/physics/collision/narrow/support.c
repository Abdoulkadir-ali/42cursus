/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:03:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_support_fn	get_support(int type)
{
	if (type == PRIM_SPHERE)
		return (gjk_support_sphere);
	if (type == PRIM_BOX)
		return (gjk_support_box);
	if (type == PRIM_CAPSULE)
		return (gjk_support_capsule);
	if (type == PRIM_CYLINDER)
		return (gjk_support_cylinder);
	if (type == PRIM_RECT)
		return (gjk_support_rect);
	if (type == PRIM_TRIANGLE)
		return (gjk_support_tri);
	if (type == PRIM_PYRAMID)
		return (gjk_support_pyramid);
	return (gjk_support_box);
}

void	init_gjk_shape(t_gjk_shape *s, t_physics *phys, int idx)
{
	int	p_idx;

	s->scene = phys->scene;
	s->phys = phys;
	s->idx = idx;
	p_idx = phys->scene->primitives.phys_idx[idx];
	if (p_idx >= 0 && phys->soa->is_compound[p_idx])
		s->support = gjk_support_compound;
	else
		s->support = get_support(phys->scene->primitives.types[idx]);
}

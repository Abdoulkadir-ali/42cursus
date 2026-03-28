/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:03:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_prim(t_physics *phys, int idx, t_contact *c, int count, int max)
{
	int	type;

	type = phys->scene->primitives.types[idx];
	if (type == PRIM_SPHERE)
		return (query_sphere(phys, idx, c, count, max));
	if (type == PRIM_BOX)
		return (query_box(phys, idx, c, count, max));
	if (type == PRIM_RECT)
		return (query_rect(phys, idx, c, count, max));
	if (type == PRIM_CAPSULE)
		return (query_capsule(phys, idx, c, count, max));
	if (type == PRIM_CYLINDER)
		return (query_cylinder(phys, idx, c, count, max));
	if (type == PRIM_PYRAMID)
		return (query_pyramid(phys, idx, c, count, max));
	if (type == PRIM_TRIANGLE)
		return (query_tri(phys, idx, c, count, max));
	return (count);
}

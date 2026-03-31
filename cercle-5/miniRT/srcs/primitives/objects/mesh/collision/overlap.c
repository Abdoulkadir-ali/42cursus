/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "physics.h"
#include "mesh.h"

/**
 * Checks if two Axis-Aligned Bounding Boxes overlap.
 */
bool	mesh_aabb_overlap(const t_aabb *a, const t_aabb *b)
{
	if (a->max.x < b->min.x || a->min.x > b->max.x)
		return (false);
	if (a->max.y < b->min.y || a->min.y > b->max.y)
		return (false);
	if (a->max.z < b->min.z || a->min.z > b->max.z)
		return (false);
	return (true);
}

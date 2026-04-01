/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 14:36:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Sweeps from left to right along bins to calculate prefix-sum areas 
 * and counts for SAH evaluation.
 */
void	bvh_sweep_left(t_bin *bins, double *left_area, int *left_counts)
{
	t_aabb	left_box;
	int		left_count;
	int		i;

	left_box = aabb_create_empty();
	left_count = 0;
	i = 0;
	while (i < BVH_BINS - 1)
	{
		left_count += bins[i].count;
		left_box = aabb_union(&left_box, &bins[i].bounds);
		left_counts[i] = left_count;
		left_area[i] = aabb_surface_area(left_box);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:37:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Returns the centroid component for @axis on item @i.
 */
static double	item_coord(t_build_item *items, size_t i, int axis)
{
	if (axis == 0)
		return (items[i].centroid.x);
	if (axis == 1)
		return (items[i].centroid.y);
	return (items[i].centroid.z);
}

/**
 * Maps a centroid coordinate @c to a bin index in [0, BVH_BINS).
 */
static size_t	centroid_bin(double c, t_sweep *sw)
{
	size_t	b;

	b = (size_t)((c - sw->lo) * sw->inv * BVH_BINS);
	if (b >= BVH_BINS)
		b = BVH_BINS - 1;
	return (b);
}

/**
 * Initialises every bin in @sw to an empty AABB with zero count.
 */
void	init_bins(t_sweep *sw)
{
	size_t	i;

	i = 0;
	while (i < BVH_BINS)
	{
		sw->bboxes[i] = aabb_create_empty();
		sw->cnts[i++] = 0;
	}
}

/**
 * Assigns each build item to its bin based on centroid position along the axis.
 */
void	fill_bins(t_sweep *sw, t_build_item *items, size_t count)
{
	size_t	i;
	size_t	b;

	i = 0;
	while (i < count)
	{
		b = centroid_bin(item_coord(items, i, sw->axis), sw);
		sw->bboxes[b] = aabb_union(&sw->bboxes[b], &items[i].bbox);
		sw->cnts[b]++;
		i++;
	}
}

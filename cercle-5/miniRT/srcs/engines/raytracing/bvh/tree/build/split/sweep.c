/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:01:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Evaluates the SAH cost of a bin-boundary split at position @b.
 * Updates @info when a better (lower-cost) split is found.
 */
static void	eval_split(t_sweep *sw, t_split_info *info, size_t count, size_t b)
{
	t_aabb	left;
	t_aabb	right;
	size_t	nl;
	size_t	i;
	double	c;

	left = aabb_create_empty();
	right = aabb_create_empty();
	nl = 0;
	i = 0;
	while (i < b)
	{
		left = aabb_union(&left, &sw->bboxes[i]);
		nl += sw->cnts[i++];
	}
	i = b;
	while (i < BVH_BINS)
		right = aabb_union(&right, &sw->bboxes[i++]);
	c = aabb_surface_area(left) * nl + aabb_surface_area(right) * (count - nl);
	if (nl > 0 && nl < count && c < info->cost)
	{
		info->cost = c;
			info->axis = init_index(sw->axis, false);
		info->split = nl;
	}
}

/**
 * Sweeps all BVH_BINS-1 candidate splits along sw->axis,
 * updating @info with the lowest-SAH position found.
 */
static void	sweep_axis(t_sweep *sw, t_build_item *items,
			size_t count, t_split_info *info)
{
	double	extent;
	size_t	b;

	extent = sw->hi - sw->lo;
	if (extent < 1e-9)
		return ;
	sw->inv = 1.0 / extent;
	init_bins(sw);
	fill_bins(sw, items, count);
	b = 1;
	while (b < BVH_BINS)
		eval_split(sw, info, count, b++);
}

/**
 * Finds the lowest-cost SAH split across all three axes using binned BVH.
 * Leaves info->axis at -1 (set by caller) when no valid split is found.
 */
void	find_best_split(t_build_item *items, size_t count,
		t_split_info *info, t_aabb *bounds)
{
	t_sweep	sw;

	info->cost = 1e30;
	sw.lo = bounds->min.x;
	sw.hi = bounds->max.x;
	sw.axis = 0;
	sweep_axis(&sw, items, count, info);
	sw.lo = bounds->min.y;
	sw.hi = bounds->max.y;
	sw.axis = 1;
	sweep_axis(&sw, items, count, info);
	sw.lo = bounds->min.z;
	sw.hi = bounds->max.z;
	sw.axis = 2;
	sweep_axis(&sw, items, count, info);
}

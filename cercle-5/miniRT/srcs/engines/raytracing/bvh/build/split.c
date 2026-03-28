/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:04:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

#define SAH_BINS 16

typedef struct s_sah_bin
{
	t_aabb	bounds;
	int		count;
}	t_sah_bin;

/**
 * @brief Performs high-performance O(n) binning for SAH split evaluation.
 * Uses pre-computed centroids to avoid redundant floating-point calculations.
 */
static void	fill_bins(t_build_item *items, size_t count, t_sah_bin *bins,
				int axis, float min_c, float scale)
{
	size_t	i;
	int		bin_idx;
	float	val;

	i = 0;
	while (i < count)
	{
		val = ((double *)&items[i].centroid.x)[axis];
		bin_idx = (int)((val - min_c) * scale);
		if (bin_idx < 0) bin_idx = 0;
		if (bin_idx >= SAH_BINS) bin_idx = SAH_BINS - 1;
		bins[bin_idx].count++;
		bins[bin_idx].bounds = aabb_union(&bins[bin_idx].bounds, &items[i].bbox);
		i++;
	}
}

/**
 * @brief Evaluates all possible splits in O(SAH_BINS) after binning.
 */
static void	eval_bins(t_sah_bin *bins, float p_area, t_split_info *info, int axis)
{
	t_aabb	left_box[SAH_BINS - 1];
	t_aabb	right_box[SAH_BINS - 1];
	int		left_cnt[SAH_BINS - 1];
	int		right_cnt[SAH_BINS - 1];
	int		i;
	float	cost;

	/* Forward pass */
	left_box[0] = bins[0].bounds; left_cnt[0] = bins[0].count;
	i = 0;
	while (++i < SAH_BINS - 1)
	{
		left_box[i] = aabb_union(&left_box[i - 1], &bins[i].bounds);
		left_cnt[i] = left_cnt[i - 1] + bins[i].count;
	}
	/* Backward pass */
	right_box[SAH_BINS - 2] = bins[SAH_BINS - 1].bounds;
	right_cnt[SAH_BINS - 2] = bins[SAH_BINS - 1].count;
	i = SAH_BINS - 2;
	while (--i >= 0)
	{
		right_box[i] = aabb_union(&right_box[i + 1], &bins[i + 1].bounds);
		right_cnt[i] = right_cnt[i + 1] + bins[i + 1].count;
	}
	/* Select min cost */
	i = -1;
	while (++i < SAH_BINS - 1)
	{
		cost = 1.0f + (aabb_surface_area(&left_box[i]) / p_area) * left_cnt[i]
				+ (aabb_surface_area(&right_box[i]) / p_area) * right_cnt[i];
		if (cost < info->cost)
		{
			info->cost = (double)cost; info->axis = axis; info->split_idx = i;
		}
	}
}

/**
 * @brief DOD-optimized split search using 16-bin Surface Area Heuristic.
 */
t_split_info	find_best_split(t_build_item *items, size_t count, double p_area)
{
	t_split_info	info;
	t_sah_bin		bins[SAH_BINS];
	t_aabb			centroid_bounds;
	int				a;

	info.axis = -1; info.cost = (double)count;
	centroid_bounds = aabb_create_empty();
	a = -1;
	while (++a < (int)count)
		aabb_expand_point(&centroid_bounds, items[a].centroid);
	a = -1;
	while (++a < 3)
	{
		float range = centroid_bounds.max[a] - centroid_bounds.min[a];
		if (range < 1e-4f) continue ;
		ft_memset(bins, 0, sizeof(bins));
		fill_bins(items, count, bins, a, centroid_bounds.min[a], (float)SAH_BINS / range);
		eval_bins(bins, (float)p_area, &info, a);
	}
	if (info.axis != -1)
	{
		size_t split = 0;
		float range = centroid_bounds.max[info.axis] - centroid_bounds.min[info.axis];
		float min_c = centroid_bounds.min[info.axis];
		float scale = (float)SAH_BINS / range;
		size_t i = 0;
		while (i < count)
		{
			float val = ((double *)&items[i].centroid.x)[info.axis];
			int b = (int)((val - min_c) * scale);
			if (b < 0)
				b = 0;
			if (b >= SAH_BINS)
				b = SAH_BINS - 1;
			if ((size_t)b <= info.split_idx)
			{
				t_build_item tmp = items[i];
				items[i] = items[split];
				items[split] = tmp;
				split++;
			}
			i++;
		}
		info.split_idx = split;
		if (split == 0 || split == count) info.axis = -1;
	}
	return (info);
}

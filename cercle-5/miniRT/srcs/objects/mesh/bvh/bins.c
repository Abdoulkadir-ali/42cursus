/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_bins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	bvh_bins_init(t_bin *bins)
{
	int	i;

	i = 0;
	while (i < BVH_BINS)
	{
		bins[i].count = 0;
		bins[i].bounds = aabb_create_empty();
		i++;
	}
}

void	bvh_fill_bins(t_bvh_bins_ctx *b)
{
	double	val;
	int		bin_idx;
	int		i;

	i = 0;
	while (i < b->count)
	{
		if (b->axis == 0)
			val = b->ctx->items[b->first + i].centroid.x;
		else if (b->axis == 1)
			val = b->ctx->items[b->first + i].centroid.y;
		else
			val = b->ctx->items[b->first + i].centroid.z;
		bin_idx = (int)((val - b->min_val) * b->scale);
		if (bin_idx >= BVH_BINS)
			bin_idx = BVH_BINS - 1;
		if (bin_idx < 0)
			bin_idx = 0;
		b->bins[bin_idx].count++;
		b->bins[bin_idx].bounds = aabb_union(&b->bins[bin_idx].bounds,
				&b->ctx->items[b->first + i].bbox);
		i++;
	}
}

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

static void	bvh_update_best(t_bvh_sah *s, int axis, int l_c)
{
	double	cost;

	if (l_c == 0 || s->right_count == 0)
		return ;
	cost = 1.0 + (s->left_area[s->i - 1] / s->parent_sa) * l_c
		+ (aabb_surface_area(s->right_box) / s->parent_sa) * s->right_count;
	if (cost >= s->best_cost)
		return ;
	s->best_cost = cost;
	s->best_axis = axis;
	s->split_pos = s->min_val + (s->i * (s->max_val - s->min_val)) / BVH_BINS;
}

void	bvh_sweep_right(t_bvh_sah *s, int axis)
{
	int		l_c;

	s->right_box = aabb_create_empty();
	s->right_count = 0;
	s->i = BVH_BINS - 1;
	while (s->i > 0)
	{
		s->right_count += s->bins[s->i].count;
		s->right_box = aabb_union(&s->right_box, &s->bins[s->i].bounds);
		l_c = s->left_counts[s->i - 1];
		bvh_update_best(s, axis, l_c);
		s->i--;
	}
}

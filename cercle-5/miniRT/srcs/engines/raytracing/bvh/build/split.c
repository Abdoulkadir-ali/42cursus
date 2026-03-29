/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                            +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	fill_bins(t_build_item *items, size_t count, t_sah_bin *bins,
				t_vec3 mc_sc)
{
	size_t	i;
	int		bin_idx;
	float	val;

	i = 0;
	while (i < count)
	{
		val = (float)((double *)&items[i].centroid.x)[(int)mc_sc.x];
		bin_idx = (int)((val - mc_sc.y) * mc_sc.z);
		if (bin_idx < 0)
			bin_idx = 0;
		if (bin_idx >= BVH_BINS)
			bin_idx = BVH_BINS - 1;
		bins[bin_idx].count++;
		bins[bin_idx].bounds = aabb_union(&bins[bin_idx].bounds, &items[i].bbox);
		i++;
	}
}

static void	eval_bins(t_sah_bin *bins, double p_area, t_split_info *info, int ax)
{
	t_aabb	lbx[BVH_BINS];
	t_aabb	rbx[BVH_BINS];
	int		lc[BVH_BINS];
	int		rc[BVH_BINS];
	int		i;
	double	cost;

	lbx[0] = bins[0].bounds;
	lc[0] = bins[0].count;
	i = 0;
	while (++i < BVH_BINS - 1)
	{
		lbx[i] = aabb_union(&lbx[i - 1], &bins[i].bounds);
		lc[i] = lc[i - 1] + bins[i].count;
	}
	rbx[BVH_BINS - 2] = bins[BVH_BINS - 1].bounds;
	rc[BVH_BINS - 2] = bins[BVH_BINS - 1].count;
	i = BVH_BINS - 2;
	while (--i >= 0)
	{
		rbx[i] = aabb_union(&rbx[i + 1], &bins[i + 1].bounds);
		rc[i] = rc[i + 1] + bins[i + 1].count;
	}
	i = -1;
	while (++i < BVH_BINS - 1)
	{
		cost = 1.0 + (aabb_surface_area(&lbx[i]) / p_area) * lc[i]
			+ (aabb_surface_area(&rbx[i]) / p_area) * rc[i];
		if (cost < info->cost && (info->cost = cost))
		{
			info->axis = ax;
			info->split_idx = (size_t)i;
		}
	}
}

static void	partition_items(t_build_item *items, size_t count,
		t_split_info *info, t_aabb cent)
{
	size_t			s_i[2];
	float			p[2];
	int				b;
	t_build_item	tmp;

	s_i[0] = 0;
	p[0] = (float)((double *)&cent.min.x)[info->axis];
	p[1] = (float)BVH_BINS / ((float)((double *)&cent.max.x)[info->axis] - p[0]);
	s_i[1] = -1;
	while (++s_i[1] < count)
	{
		b = (int)((((double *)&items[s_i[1]].centroid.x)[info->axis] - p[0]) * p[1]);
		if (b < 0)
			b = 0;
		if (b >= BVH_BINS)
			b = BVH_BINS - 1;
		if ((size_t)b <= info->split_idx)
		{
			tmp = items[s_i[1]];
			items[s_i[1]] = items[s_i[0]];
			items[s_i[0]++] = tmp;
		}
	}
	info->split_idx = s_i[0];
	if (s_i[0] == 0 || s_i[0] == count)
		info->axis = -1;
}

t_split_info	find_best_split(t_build_item *items, size_t count, double p_area)
{
	t_split_info	info;
	t_sah_bin		bins[BVH_BINS];
	t_aabb			cent;
	int				a;
	float			r;

	info.axis = -1;
	info.cost = (double)count;
	cent = aabb_create_empty();
	a = -1;
	while (++a < (int)count)
		aabb_expand_point(&cent, items[a].centroid);
	a = -1;
	while (++a < 3)
	{
		r = (float)((double *)&cent.max.x)[a] - (float)((double *)&cent.min.x)[a];
		if (r < 1e-4f)
			continue ;
		ft_memset(bins, 0, sizeof(bins));
		fill_bins(items, count, bins, vec3((double)a,
				(double)((double *)&cent.min.x)[a], (double)BVH_BINS / (double)r));
		eval_bins(bins, p_area, &info, a);
	}
	if (info.axis != -1)
		partition_items(items, count, &info, cent);
	return (info);
}

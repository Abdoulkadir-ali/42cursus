/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	compute_split_cost(t_build_item *items, size_t split,
		size_t count, double p_area)
{
	t_aabb	left_box;
	t_aabb	right_box;
	size_t	i;
	double	cost;

	left_box = aabb_create_empty();
	right_box = aabb_create_empty();
	i = 0;
	while (i < split)
	{
		left_box = aabb_union(&left_box, &items[i].bbox);
		i++;
	}
	while (i < count)
	{
		right_box = aabb_union(&right_box, &items[i].bbox);
		i++;
	}
	cost = 1.0 + (aabb_surface_area(left_box) / p_area) * split * 2.0
		+ (aabb_surface_area(right_box) / p_area) * (count - split) * 2.0;
	return (cost);
}

static void	find_best_split_for_axis(t_build_item *items, size_t count,
				double p_area, t_split_info *info)
{
	int		s;
	size_t	split;
	double	cost;

	s = 1;
	while (s < 32)
	{
		split = (count * s) / 32;
		if (split < 1 || split >= count)
		{
			s++;
			continue ;
		}
		cost = compute_split_cost(items, split, count, p_area);
		if (cost < info->cost)
		{
			info->cost = cost;
			info->split = split;
		}
		s++;
	}
}

static t_split_info	try_axis_splits(t_build_item *items, size_t count,
						double p_area, int axis)
{
	t_split_info	info;

	if (axis == 0)
		qsort(items, count, sizeof(t_build_item), compare_x);
	else if (axis == 1)
		qsort(items, count, sizeof(t_build_item), compare_y);
	else
		qsort(items, count, sizeof(t_build_item), compare_z);
	info.axis = axis;
	info.split = 0;
	info.cost = count * 2.0;
	find_best_split_for_axis(items, count, p_area, &info);
	return (info);
}

t_split_info	find_best_split(t_build_item *items, size_t count,
		double p_area)
{
	t_split_info	info;
	int				axis;
	t_split_info	axis_info;

	info.axis = -1;
	info.split = 0;
	info.cost = count * 2.0;
	axis = 0;
	while (axis < 3)
	{
		axis_info = try_axis_splits(items, count, p_area, axis);
		if (axis_info.cost < info.cost)
			info = axis_info;
		axis++;
	}
	return (info);
}

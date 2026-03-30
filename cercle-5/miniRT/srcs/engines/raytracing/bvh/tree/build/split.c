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

static t_split_info	find_best_split_fast(t_build_item *items, size_t count,
						double p_area, int axis)
{
	t_aabb			*prefix;
	t_aabb			*suffix;
	t_split_info	info;
	size_t			i;
	double			cost;

	prefix = malloc(sizeof(t_aabb) * count);
	suffix = malloc(sizeof(t_aabb) * count);
	if (!prefix || !suffix)
	{
		free(prefix);
		free(suffix);
		return ((t_split_info){axis, count / 2, (double)count * 2.1});
	}
	prefix[0] = items[0].bbox;
	i = 0;
	while (++i < count)
		prefix[i] = aabb_union(&prefix[i - 1], &items[i].bbox);
	suffix[count - 1] = items[count - 1].bbox;
	i = count - 1;
	while (i-- > 0)
		suffix[i] = aabb_union(&suffix[i + 1], &items[i].bbox);
	info = (t_split_info){axis, 0, (double)count * 2.0};
	i = 0;
	while (++i < count)
	{
		cost = 1.0 + (aabb_surface_area(prefix[i - 1]) / p_area) * i * 2.0
			+ (aabb_surface_area(suffix[i]) / p_area) * (count - i) * 2.0;
		if (cost < info.cost)
		{
			info.cost = cost;
			info.split = i;
		}
	}
	free(prefix);
	free(suffix);
	return (info);
}

t_split_info	find_best_split(t_build_item *items, size_t count,
		double p_area)
{
	t_split_info	best;
	t_split_info	current;
	int				axis;

	best.axis = -1;
	best.split = 0;
	best.cost = (double)count * 2.0;
	axis = -1;
	while (++axis < 3)
	{
		if (axis == 0)
			qsort(items, count, sizeof(t_build_item), compare_x);
		else if (axis == 1)
			qsort(items, count, sizeof(t_build_item), compare_y);
		else
			qsort(items, count, sizeof(t_build_item), compare_z);
		current = find_best_split_fast(items, count, p_area, axis);
		if (current.split > 0 && current.split < count
			&& current.cost < best.cost)
			best = current;
	}
	return (best);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static double	get_centroid_val(t_bvh_bins *b, size_t i)
{
	if (b->axis == 0)
		return (b->bvh->items[b->first + i].centroid.x);
	if (b->axis == 1)
		return (b->bvh->items[b->first + i].centroid.y);
	return (b->bvh->items[b->first + i].centroid.z);
}

/**
 * Fills bins based on triangle centroids along a specified axis.
 */
void	bvh_fill_bins(t_bvh_bins *b)
{
	size_t	i;
	double	val;
	int		bin_idx;

	i = 0;
	while (i < b->count)
	{
		val = get_centroid_val(b, i);
		bin_idx = (val - b->min_val) * b->scale;
		if (bin_idx >= BVH_BINS)
			bin_idx = BVH_BINS - 1;
		if (bin_idx < 0)
			bin_idx = 0;
		b->bins[bin_idx].count++;
		b->bins[bin_idx].bounds = aabb_union(&b->bins[bin_idx].bounds,
				&b->bvh->items[b->first + i].bbox);
		i++;
	}
}

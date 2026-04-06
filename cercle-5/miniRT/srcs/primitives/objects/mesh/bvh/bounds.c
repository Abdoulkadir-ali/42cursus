/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_bounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

void	bvh_update_node_bounds(t_mbvh_node *node, t_mbvh *bvh, size_t first,
		size_t count)
{
	t_aabb	bbox;
	size_t	i;

	bbox = aabb_create_empty();
	i = 0;
	while (i < count)
	{
		bbox = aabb_union(&bbox, &bvh->items[first + i].bbox);
		i++;
	}
	node->bbox = bbox;
}

void	bvh_centroid_bounds(t_mbvh *bvh, int first, int count, t_aabb *out)
{
	t_aabb	bounds;
	int		i;

	bounds = aabb_create_empty();
	i = 0;
	while (i < count)
	{
		aabb_expand_point(&bounds, bvh->items[first + i].centroid);
		i++;
	}
	*out = bounds;
}

void	bvh_axis_min_max(t_aabb *bounds, size_t axis, double *min_val,
		double *max_val)
{
	if (axis == 0)
	{
		*min_val = bounds->min.x;
		*max_val = bounds->max.x;
	}
	else if (axis == 1)
	{
		*min_val = bounds->min.y;
		*max_val = bounds->max.y;
	}
	else
	{
		*min_val = bounds->min.z;
		*max_val = bounds->max.z;
	}
}

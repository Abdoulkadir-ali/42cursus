/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:55:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static double	bvh_item_centroid(t_mesh_build_item *items, size_t idx, size_t axis)
{
	if (axis == 0)
		return (items[idx].centroid.x);
	if (axis == 1)
		return (items[idx].centroid.y);
	return (items[idx].centroid.z);
}

static void	bvh_swap_item(t_mesh_build_item *items, size_t left, size_t right)
{
	t_mesh_build_item	tmp;

	tmp = items[left];
	items[left] = items[right];
	items[right] = tmp;
}

/**
 * Partitions mesh items (triangles) around a split value along a 
 * specified axis. Returns the index of the first item in the right 
 * partition.
 */
size_t	bvh_partition_items(t_mesh_build_item *items, size_t count, size_t axis,
		double split_val)
{
	size_t	left;
	size_t	right;
	double	c_val;

	left = 0;
	if (!count)
		return (0);
	right = count - 1;
	while (left <= right)
	{
		c_val = bvh_item_centroid(items, left, axis);
		if (c_val < split_val)
			left++;
		else
		{
			bvh_swap_item(items, left, right);
			right--;
		}
	}
	return (left);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:30:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Processes intersection comparisons over an array of primitive references within a flat structure leaf.
 * 
 * Once the BVH traversal locates a populated leaf bounding box matching intersection,
 * this function iterates through every object reference housed in that node.
 * It strictly overwrites the global `hit` state whenever a closer surface hit interval is flagged.
 * 
 * @param bvh      The entire bounded volume hierarchy state object handling nodes and references array.
 * @param node_idx The integer target index within the nodes array identifying the processing leaf.
 * @param ray      The active projected vector tested alongside sequential loop references.
 * @param hit      Pointer referencing the minimal hit tracked distances, updated incrementally.
 * 
 * @return Function manages in-place reference changes seamlessly without return properties.
 */
void	process_leaf_flat(const t_bvh *bvh, int node_idx, const t_ray *ray,
		t_hit *hit)
{
	const t_bvh_node	*node;
	t_hit				temp;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end)
	{
		temp.t = MAX_VALUE;
		temp.ref.type = TYPE_NONE;
		if (intersect_object(ray, bvh->scene, bvh->refs[i], &temp)
			&& temp.t < hit->t)
			*hit = temp;
		i++;
	}
}

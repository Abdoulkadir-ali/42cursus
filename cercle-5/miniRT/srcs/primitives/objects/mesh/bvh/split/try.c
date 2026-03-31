/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Attempts to find an optimal split for a BVH node and partitions its items. 
 * It wraps the split search and partitioning logic into a single high-level 
 * operation used during recursive construction.
 */
bool	bvh_try_split(t_bvh_try *bvh)
{
	t_bvh_find	find;

	find.bvh = bvh->bvh;
	find.node = bvh->node;
	find.first = bvh->first;
	find.count = bvh->count;
	find.out = bvh->split;
	if (!bvh_find_split(&find))
		return (false);
	*bvh->mid = bvh_partition_items(&bvh->bvh->items[bvh->first],
			bvh->count, bvh->split->axis, bvh->split->pos);
	if (*bvh->mid == 0 || *bvh->mid == bvh->count)
		return (false);
	return (true);
}

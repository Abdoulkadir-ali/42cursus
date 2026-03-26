/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:44:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Dispatcher sorting the leaf nodes and handling recursive hierarchical tree branch actions.
 * 
 * Invokes leaf evaluation iterations if elements are found clustered. Otherwise,
 * it bridges back into the tree by delegating the branch splitting routines.
 * 
 * @param bvh Structure pointing to the stack pointer tracking bounds.
 * @param hit Closest recorded intersection information state.
 * @param i   Node integer parameter identifying positional indices recursively.
 * 
 * @return Does not return explicitly. Alters hit outputs natively.
 */
static void	process_node(t_bvh_stack *bvh, t_hit *hit, int i)
{
	if (bvh->bvh->nodes[i].count > 0)
		process_leaf_flat(bvh->bvh, i, bvh->ray, hit);
	else if (bvh->ptr < 124)
	{
		bvh->hit_t = hit->t;
		push_children(bvh, i);
	}
}

/**
 * @brief Topmost processing mechanism parsing tree boundaries efficiently in continuous unrolled loop form.
 * 
 * Extracts performance by mimicking hierarchical iteration recursively without
 * standard overheads using local stacks. Tracks `t_min` parameters strictly discarding
 * bounding box tests that register past previously mapped intersection geometry ranges.
 * 
 * @param bvh Central object encompassing virtual structure boundaries globally parsed.
 * @param ray Directional ray mapping testing vector coordinates against shape proximities.
 * @param hit Active mapping memory writing successful shape references inside nodes.
 * 
 * @return True validates complete intersection confirming geometry references. Discards hits with false.
 */
bool	run_traverse_loop(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	int				st[128];
	double			st_tmin[128];
	t_bvh_stack	bvh;

	bvh.stack = st;
	bvh.stack_tmin = st_tmin;
	bvh.ptr = 1;
	bvh.bvh = bvh;
	bvh.ray = ray;
	bvh.stack[0] = 0;
	bvh.stack_tmin[0] = 0.0;
	while (bvh.ptr > 0)
	{
		bvh.ptr--;
		if (bvh.stack_tmin[bvh.ptr] <= hit->t)
			process_node(&bvh, hit, bvh.stack[bvh.ptr]);
	}
	return (hit->ref.type != TYPE_NONE);
}

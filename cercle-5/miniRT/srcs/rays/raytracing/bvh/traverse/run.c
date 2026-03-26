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
static void	traverse_node(t_bvh_stack *s, t_hit *hit, int i)
{
	if (s->bvh->nodes[i].count > 0)
		process_leaf_flat(s->bvh, i, s->ray, hit);
	else if (s->ptr < 124)
	{
		s->hit_t = hit->t;
		push_children(s, i);
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
	t_bvh_stack	s;

	s.stack = st;
	s.stack_tmin = st_tmin;
	s.ptr = 1;
	s.bvh = bvh;
	s.ray = ray;
	s.stack[0] = 0;
	s.stack_tmin[0] = 0.0;
	while (s.ptr > 0)
	{
		s.ptr--;
		if (s.stack_tmin[s.ptr] <= hit->t)
			traverse_node(&s, hit, s.stack[s.ptr]);
	}
	return (hit->ref.type != TYPE_NONE);
}

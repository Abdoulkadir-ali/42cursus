/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:56:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

size_t	push_node(t_bvh *bvh)
{
	t_bvh_node	*tmp;
	size_t		new_cap;

	if (bvh->n_nodes >= bvh->cap_nodes)
	{
		new_cap = 64;
		if (bvh->cap_nodes)
			new_cap = bvh->cap_nodes * 2;
		tmp = realloc(bvh->nodes, sizeof(t_bvh_node) * new_cap);
		if (!tmp)
			return (0);
		bvh->nodes = tmp;
		bvh->cap_nodes = new_cap;
	}
	bvh->nodes[bvh->n_nodes].simd_idx = -1;
	return (bvh->n_nodes++);
}

void	make_leaf(t_bvh *bvh, t_task t, const t_aabb *boxes, size_t *idx)
{
	t_aabb	b;
	size_t	i;

	aabb_reset(&b);
	i = t.start;
	while (i < t.end)
	{
		aabb_union(&b, &boxes[idx[i]]);
		i++;
	}
	bvh->nodes[t.node].box = b;
	bvh->nodes[t.node].first = t.start;
	bvh->nodes[t.node].count = t.end - t.start;
}

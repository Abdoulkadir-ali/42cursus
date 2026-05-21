/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:04 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:56:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	refit_leaf(t_bvh *bvh, t_bvh_node *n, const t_object *objs)
{
	t_aabb	b;
	t_aabb	tb;
	size_t	j;
	size_t	end;

	aabb_reset(&b);
	j = n->first;
	end = n->first + n->count;
	while (j < end)
	{
		tb = obj_box(&objs[bvh->indices[j]]);
		aabb_union(&b, &tb);
		j++;
	}
	n->box = b;
}

void	bvh_refit(t_bvh *bvh, const t_object *objs)
{
	t_bvh_node	*n;
	t_aabb		b;
	size_t		i;

	if (!bvh || bvh->n_nodes <= 0)
		return ;
	i = bvh->n_nodes;
	while (i > 0)
	{
		i--;
		n = &bvh->nodes[i];
		if (n->count > 0)
			refit_leaf(bvh, n, objs);
		else
		{
			b = bvh->nodes[n->first].box;
			aabb_union(&b, &bvh->nodes[n->first + 1].box);
			n->box = b;
		}
	}
}

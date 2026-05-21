/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subdivide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:55:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:20:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	subdivide(t_bvh *bvh, t_task t, t_sah *s, t_task out[2])
{
	t_sah_out	so;
	size_t		nodes[2];
	size_t		n;

	n = t.end - t.start;
	if (n <= 4)
		return (0);
	s->n = n;
	s->idx = bvh->indices + t.start;
	if (!sah_choose_axis(s, &so))
		return (0);
	nodes[0] = push_node(bvh);
	nodes[1] = push_node(bvh);
	if (nodes[0] == (size_t)-1 || nodes[1] == (size_t)-1)
		return (-1);
	bvh->nodes[t.node].box = so.left;
	aabb_union(&bvh->nodes[t.node].box, &so.right);
	bvh->nodes[t.node].first = nodes[0];
	bvh->nodes[t.node].count = 0;
	bvh->nodes[nodes[0]].box = so.left;
	bvh->nodes[nodes[1]].box = so.right;
	out[0] = (t_task){nodes[0], t.start, t.start + so.split};
	out[1] = (t_task){nodes[1], t.start + so.split, t.end};
	return (1);
}

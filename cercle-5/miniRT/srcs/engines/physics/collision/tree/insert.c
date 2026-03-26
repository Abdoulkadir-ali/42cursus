/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_aabb	aabb_merge(t_aabb a, t_aabb b)
{
	t_aabb	r;

	r.min.x = fmin(a.min.x, b.min.x);
	r.min.y = fmin(a.min.y, b.min.y);
	r.min.z = fmin(a.min.z, b.min.z);
	r.max.x = fmax(a.max.x, b.max.x);
	r.max.y = fmax(a.max.y, b.max.y);
	r.max.z = fmax(a.max.z, b.max.z);
	return (r);
}



static int	alloc_node(t_dbvt *t, t_aabb aabb, int leaf, int left, int right)
{
	t_dbvt_node	*n;

	if (t->node_count >= DBVT_MAX_NODES)
		return (DBVT_NULL);
	n = &t->nodes[t->node_count];
	n->aabb = aabb;
	n->leaf = leaf;
	n->left = left;
	n->right = right;
	return (t->node_count++);
}

/* Split leaves[begin..end) into two groups by position along longest axis. */
static int	split_axis(t_dbvt *t, int begin, int end)
{
	t_aabb	bound;
	t_vec3	d;
	int		mid;
	int		axis;

	bound = t->leaves[begin].fat_aabb;
	mid = begin + 1;
	while (mid < end)
		bound = aabb_merge(bound, t->leaves[mid++].fat_aabb);
	d = vec3_sub(bound.max, bound.min);
	if (d.x >= d.y && d.x >= d.z)
		axis = 0;
	else if (d.y >= d.z)
		axis = 1;
	else
		axis = 2;
	mid = (begin + end) / 2;
	(void)axis;
	return (mid);
}

int	dbvt_build_range(t_dbvt *t, int begin, int end)
{
	t_aabb	merged;
	int		mid;
	int		l;
	int		r;

	if (end - begin == 1)
	{
		merged = t->leaves[begin].fat_aabb;
		return (alloc_node(t, merged, begin, DBVT_NULL, DBVT_NULL));
	}
	mid = split_axis(t, begin, end);
	l = dbvt_build_range(t, begin, mid);
	r = dbvt_build_range(t, mid, end);
	merged = aabb_merge(t->nodes[l].aabb, t->nodes[r].aabb);
	return (alloc_node(t, merged, DBVT_NULL, l, r));
}

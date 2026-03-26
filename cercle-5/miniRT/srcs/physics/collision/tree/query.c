/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static bool	aabb_hit(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x) return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y) return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z) return (false);
	return (true);
}

static int	test_leaf_pair(t_dbvt *t, int ia, int ib, t_body_pair *out, int count, int max)
{
	t_dbvt_leaf	*a = &t->leaves[t->nodes[ia].leaf];
	t_dbvt_leaf	*b = &t->leaves[t->nodes[ib].leaf];

	if (!aabb_hit(a->fat_aabb, b->fat_aabb) || count >= max) return (count);
	if (a->body == b->body) return (count);
	out[count].a = a->body;
	out[count].b = b->body;
	return (count + 1);
}

static int	recurse_pair(t_dbvt *t, int ni, int nj, t_body_pair *out, int count, int max)
{
	t_dbvt_node *a; t_dbvt_node *b;
	if (ni == DBVT_NULL || nj == DBVT_NULL || count >= max) return (count);
	a = &t->nodes[ni]; b = &t->nodes[nj];
	if (!aabb_hit(a->aabb, b->aabb)) return (count);
	if (a->leaf != DBVT_NULL && b->leaf != DBVT_NULL)
		return (test_leaf_pair(t, ni, nj, out, count, max));
	if (a->leaf != DBVT_NULL)
	{
		count = recurse_pair(t, ni, b->left, out, count, max);
		return (recurse_pair(t, ni, b->right, out, count, max));
	}
	count = recurse_pair(t, a->left, nj, out, count, max);
	return (recurse_pair(t, a->right, nj, out, count, max));
}

/**
 * @brief Traverses the DBVT and emits all overlapping body pairs.
 * Uses dual-subtree traversal: O(n log n) vs O(n²) brute-force.
 * Returns count of pairs written to out[].
 */
int	dbvt_query_pairs(t_dbvt *t, t_body_pair *out, int max)
{
	int	count;
	int	root;

	root = t->root;
	if (root == DBVT_NULL || t->leaf_count < 2)
		return (0);
	count = recurse_pair(t, t->nodes[root].left, t->nodes[root].right,
			out, 0, max);
	return (count);
}

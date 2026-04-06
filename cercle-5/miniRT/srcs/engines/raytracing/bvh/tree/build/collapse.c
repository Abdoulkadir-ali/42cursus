/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static size_t	pick_expand(const t_bvh *bvh, const size_t *ch, size_t n)
{
	size_t	best;
	double	best_sa;
	double	sa;
	size_t	i;

	best = n;
	best_sa = -1.0;
	i = 0;
	while (i < n)
	{
		if (bvh->nodes[ch[i]].count == 0)
		{
			sa = aabb_surface_area(bvh->nodes[ch[i]].bbox);
			if (sa > best_sa)
			{
				best_sa = sa;
				best = i;
			}
		}
		i++;
	}
	return (best);
}

static size_t	gather_children(const t_bvh *bvh, size_t idx, size_t *ch)
{
	const t_bvh_node	*nd;
	size_t				n;
	size_t				exp;

	nd = &bvh->nodes[idx];
	ch[0] = nd->left_or_first;
	ch[1] = idx + 1;
	n = 2;
	exp = pick_expand(bvh, ch, n);
	if (exp < n)
	{
		idx = ch[exp];
		ch[exp] = bvh->nodes[idx].left_or_first;
		ch[n++] = idx + 1;
	}
	exp = pick_expand(bvh, ch, n);
	if (exp < n && n < 4)
	{
		idx = ch[exp];
		ch[exp] = bvh->nodes[idx].left_or_first;
		ch[n++] = idx + 1;
	}
	return (n);
}

static void	fill_slot(t_bvh_node4 *n4, size_t i, const t_bvh_node *c)
{
	if (!c)
	{
		n4->min_x[i] = 1e30f;
		n4->min_y[i] = 1e30f;
		n4->min_z[i] = 1e30f;
		n4->max_x[i] = -1e30f;
		n4->max_y[i] = -1e30f;
		n4->max_z[i] = -1e30f;
		n4->count[i] = 0;
		return ;
	}
	n4->min_x[i] = (float)c->bbox.min.x;
	n4->min_y[i] = (float)c->bbox.min.y;
	n4->min_z[i] = (float)c->bbox.min.z;
	n4->max_x[i] = (float)c->bbox.max.x;
	n4->max_y[i] = (float)c->bbox.max.y;
	n4->max_z[i] = (float)c->bbox.max.z;
	n4->child[i] = c->left_or_first;
	n4->count[i] = c->count;
}

static void	collapse_node(t_bvh *bvh, size_t bin_idx, size_t *next4)
{
	size_t		my4;
	t_bvh_node4	*n4;
	size_t		ch[4];
	size_t		i;

	my4 = (*next4)++;
	n4 = &bvh->nodes4[my4];
	n4->n_children = gather_children(bvh, bin_idx, ch);
	i = 0;
	while (i < n4->n_children)
	{
		fill_slot(n4, i, &bvh->nodes[ch[i]]);
		if (n4->count[i] == 0)
		{
			n4->child[i] = *next4;
			collapse_node(bvh, ch[i], next4);
		}
		i++;
	}
	while (i < 4)
		fill_slot(n4, i++, NULL);
}

void	bvh_collapse(t_bvh *bvh)
{
	size_t	next4;
	size_t	i;

	if (!bvh || bvh->num_nodes == 0)
		return ;
	next4 = ((sizeof(t_bvh_node4) * bvh->num_nodes) + 63) & ~63;
	bvh->nodes4 = aligned_alloc(64, next4);
	if (!bvh->nodes4)
		return ;
	next4 = 0;
	if (bvh->nodes[0].count > 0)
	{
		next4 = 1;
		bvh->nodes4[0].n_children = 1;
		fill_slot(&bvh->nodes4[0], 0, &bvh->nodes[0]);
		i = 1;
		while (i < 4)
			fill_slot(&bvh->nodes4[0], i++, NULL);
	}
	else
		collapse_node(bvh, 0, &next4);
	bvh->num_nodes4 = next4;
}

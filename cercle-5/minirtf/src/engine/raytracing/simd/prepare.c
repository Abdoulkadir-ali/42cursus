/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:19:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static size_t	count_leaves(t_bvh *bvh)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (i < bvh->n_nodes)
	{
		bvh->nodes[i].simd_idx = -1;
		if (bvh->nodes[i].count > 0)
			n++;
		i++;
	}
	return (n);
}

static bool	realloc_soa(t_bvh *bvh, size_t n_leaves)
{
	if (bvh->n_soa_capacity >= n_leaves)
		return (true);
	free(bvh->soa_tris);
	bvh->soa_tris = (t_tri_soa4 *)malloc(sizeof(t_tri_soa4) * n_leaves);
	if (!bvh->soa_tris)
	{
		bvh->n_soa_capacity = 0;
		return (false);
	}
	bvh->n_soa_capacity = n_leaves;
	return (true);
}

static bool	node_all_tris(const t_bvh *bvh, const t_object *objs,
		t_bvh_node *node)
{
	size_t	j;

	j = 0;
	while (j < node->count)
	{
		if (objs[bvh->indices[node->first + j]].type != OBJ_TRIANGLE)
			return (false);
		j++;
	}
	return (true);
}

void	bvh_prepare_simd(t_bvh *bvh, const t_object *objs)
{
	t_bvh_node	*node;
	size_t		n_leaves;
	size_t		i;

	n_leaves = count_leaves(bvh);
	bvh->n_soa = 0;
	if (!realloc_soa(bvh, n_leaves) || !bvh->soa_tris)
		return ;
	i = 0;
	while (i < bvh->n_nodes)
	{
		node = &bvh->nodes[i];
		if (node->count > 0 && node_all_tris(bvh, objs, node))
			assign_node_soa(bvh, objs, node);
		i++;
	}
}

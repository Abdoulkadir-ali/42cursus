/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

int	process_occ_node(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_occ_ctx *ctx)
{
	t_mbvh_node	*node;

	node = &mesh->bvh_nodes[node_idx];
	if (node->count > 0)
	{
		if (leaf_occluded(mesh, node, ray, ctx->dist))
			return (-2);
		if (ctx->top == 0)
			return (-1);
		return (ctx->stack[--ctx->top]);
	}
	node_idx = pick_occ_children(mesh, node_idx, ray, ctx);
	if (node_idx < 0 && ctx->top > 0)
		return (ctx->stack[--ctx->top]);
	return (node_idx);
}

bool	traverse_occlude(t_mesh *mesh, const t_ray *ray, double dist)
{
	t_occ_ctx	ctx;
	int			node_idx;

	ctx.top = 0;
	ctx.dist = dist;
	node_idx = 0;
	while (node_idx >= 0)
	{
		node_idx = process_occ_node(mesh, node_idx, ray, &ctx);
		if (node_idx == -2)
			return (true);
	}
	return (false);
}

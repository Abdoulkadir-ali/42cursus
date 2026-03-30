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
#include "profiler.h"

int	process_node(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_mbvh_node	*node;

	PROF_INC(g_mesh_aabb_tests);
	node = &mesh->bvh_nodes[node_idx];
	if (node->count > 0)
	{
		process_mesh_leaf(mesh, node, ray, ctx);
		if (ctx->top == 0)
			return (-1);
		return (ctx->stack[--ctx->top]);
	}
	node_idx = pick_children(mesh, node_idx, ray, ctx);
	if (node_idx < 0 && ctx->top > 0)
		return (ctx->stack[--ctx->top]);
	return (node_idx);
}

void	intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
		t_trace_ctx *ctx)
{
	int	node_idx;

	node_idx = 0;
	while (node_idx >= 0)
		node_idx = process_node(mesh, node_idx, ray, ctx);
}

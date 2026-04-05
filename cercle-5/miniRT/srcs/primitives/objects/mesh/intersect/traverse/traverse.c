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

#include "mesh.h"
#include "profiler.h"

static size_t	process_node(t_mesh *mesh, size_t node_idx, const t_ray *ray,
		t_trace *trace)
{
	t_mbvh_node	*node;
	t_index		idx;

	PROF_INC(g_mesh_aabb_tests);
	trace->node_count++;
	node = &mesh->bvh_nodes[node_idx];
	if (node->count > 0)
	{
		process_mesh_leaf(mesh, node, ray, trace);
		if (trace->top == 0)
			return (0);
		return (trace->stack[--trace->top]);
	}
	idx = init_index(node_idx, false);
	node_idx = pick_children(mesh, idx, ray, trace);
	if (node_idx == 0 && trace->top > 0)
		return (trace->stack[--trace->top]);
	return (node_idx);
}

void	intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
		t_trace *trace)
{
	size_t	node_idx;

	node_idx = 1;
	while (node_idx != 0)
	{
		node_idx = process_node(mesh, node_idx - 1, ray, trace);
		if (node_idx != 0)
			node_idx++;
	}
}

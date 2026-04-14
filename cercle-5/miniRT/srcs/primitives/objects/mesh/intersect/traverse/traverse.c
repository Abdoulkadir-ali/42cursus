/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 08:57:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "profiler.h"

static t_index	process_node(t_mesh *mesh, size_t i, const t_ray *ray,
		t_trace *trace)
{
	t_mbvh_node	*node;
	t_index		idx;

	PROF_INC(mesh_aabb_tests);
	trace->node_count++;
	node = &mesh->bvh_nodes[i];
	if (node->count > 0)
	{
		process_mesh_leaf(mesh, node, ray, trace);
		if (trace->top == 0)
			return (init_index(0, true));
		return (init_index(trace->stack[--trace->top], false));
	}
	idx = init_index(i, false);
	idx = pick_children(mesh, idx, ray, trace);
	if (idx.error && trace->top > 0)
		return (init_index(trace->stack[--trace->top], false));
	return (idx);
}

void	intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
		t_trace *trace)
{
	t_index	idx;

	idx = init_index(0, false);
	while (!idx.error)
	{
		idx = process_node(mesh, idx.i, ray, trace);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "objects.h"

static int	bvh_make_leaf(t_mbvh_node *node, int first, int count, int node_idx)
{
	node->left_or_first = first;
	node->count = count;
	return (node_idx);
}

static bool	bvh_try_split(t_bvh_try_ctx *t)
{
	t_bvh_find_ctx	find;

	find.ctx = t->ctx;
	find.node = t->node;
	find.first = t->first;
	find.count = t->count;
	find.out = t->split;
	if (!bvh_find_split(&find))
		return (false);
	*t->mid = bvh_partition_items(t->ctx->items + t->first, t->count,
			t->split->axis, t->split->pos);
	if (*t->mid <= 0 || *t->mid >= t->count)
		return (false);
	return (true);
}

static bool	bvh_prepare_ctx(t_mbvh_ctx *ctx, t_mesh *mesh)
{
	int	i;

	ctx->items = malloc(sizeof(t_mesh_build_item) * mesh->tri_count);
	if (!ctx->items)
		return (false);
	i = 0;
	while (i < mesh->tri_count)
	{
		bvh_get_triangle_info(mesh, i, &ctx->items[i]);
		i++;
	}
	if (mesh->bvh_nodes)
		free(mesh->bvh_nodes);
	if (mesh->bvh_indices)
		free(mesh->bvh_indices);
	mesh->bvh_nodes = ft_calloc(mesh->tri_count * 2, sizeof(t_mbvh_node));
	mesh->bvh_indices = malloc(sizeof(int) * mesh->tri_count * 3);
	if (!mesh->bvh_nodes || !mesh->bvh_indices)
	{
		free(ctx->items);
		return (false);
	}
	ctx->nodes = mesh->bvh_nodes;
	ctx->node_count = 0;
	return (true);
}

static int	build_mesh_recursive(t_mbvh_ctx *ctx, int first, int count)
{
	t_mbvh_node		*node;
	t_bvh_split		split;
	t_bvh_try_ctx	try;
	int				node_idx;
	int				mid;

	node_idx = ctx->node_count++;
	node = &ctx->nodes[node_idx];
	bvh_update_node_bounds(node, ctx, first, count);
	if (count <= 4)
		return (bvh_make_leaf(node, first, count, node_idx));
	try.ctx = ctx;
	try.node = node;
	try.first = first;
	try.count = count;
	try.split = &split;
	try.mid = &mid;
	if (!bvh_try_split(&try))
		return (bvh_make_leaf(node, first, count, node_idx));
	node->count = 0;
	node->axis = split.axis;
	build_mesh_recursive(ctx, first, mid);
	node->left_or_first = build_mesh_recursive(ctx, first + mid, count - mid);
	debug_print_bvh_build(count, 0, false);
	return (node_idx);
}

void	mesh_build_bvh(t_mesh *mesh)
{
	t_mbvh_ctx	ctx;

	if (!mesh || mesh->tri_count == 0)
		return ;
	if (!bvh_prepare_ctx(&ctx, mesh))
		return ;
	build_mesh_recursive(&ctx, 0, mesh->tri_count);
	bvh_copy_indices(mesh, &ctx);
	mesh_build_tri_cache(mesh);
	debug_print_bvh_build(mesh->tri_count, 0, false);
	ft_print_debug("DEBUG: Mesh BVH built: %d nodes for %d tris\n",
		ctx.node_count, mesh->tri_count);
	free(ctx.items);
}

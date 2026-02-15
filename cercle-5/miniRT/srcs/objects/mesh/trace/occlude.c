/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trace_occlude.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "profiler.h"

static void	init_occ_ctx(t_occ_ctx *ctx)
{
	ctx->top = 0;
	ctx->node_idx = 0;
	ctx->stack[ctx->top++] = 0;
}

static bool	leaf_occluded(t_mesh *mesh, t_mbvh_node *node, const t_ray *ray,
		double dist)
{
	int		i;
	int		tri;
	double	t;

	i = 0;
	while (i < node->count)
	{
		tri = node->left_or_first + i;
		if (intersect_tri_precomp(ray, &mesh->tri_cache[tri], &t, NULL)
			&& t < dist)
			return (true);
		i++;
	}
	return (false);
}

static void	push_mesh_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_occ_ctx *ctx)
{
	t_occ_child	child;

	child.left_idx = node_idx + 1;
	child.right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	child.hit_l = aabb_intersect_fast(
			&mesh->bvh_nodes[child.left_idx].bbox, ray,
			&child.tl_min, &child.tl_max);
	child.hit_r = aabb_intersect_fast(
			&mesh->bvh_nodes[child.right_idx].bbox, ray,
			&child.tr_min, &child.tr_max);
	if (child.hit_l && child.tl_min >= ctx->dist)
		child.hit_l = false;
	if (child.hit_r && child.tr_min >= ctx->dist)
		child.hit_r = false;
	if (child.hit_l && child.hit_r)
	{
		if (child.tl_min > child.tr_min)
		{
			ctx->stack[ctx->top++] = child.left_idx;
			ctx->stack[ctx->top++] = child.right_idx;
		}
		else
		{
			ctx->stack[ctx->top++] = child.right_idx;
			ctx->stack[ctx->top++] = child.left_idx;
		}
	}
	else if (child.hit_l)
		ctx->stack[ctx->top++] = child.left_idx;
	else if (child.hit_r)
		ctx->stack[ctx->top++] = child.right_idx;
}

bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist)
{
	t_occ_ctx	ctx;
	t_mbvh_node	*node;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	PROF_INC(g_mesh_occ_calls);
	init_occ_ctx(&ctx);
	ctx.dist = dist;
	while (ctx.top > 0)
	{
		ctx.node_idx = ctx.stack[--ctx.top];
		node = &mesh->bvh_nodes[ctx.node_idx];
		if (node->count > 0)
		{
			if (leaf_occluded(mesh, node, ray, dist))
				return (true);
		}
		else
			push_mesh_children(mesh, ctx.node_idx, ray, &ctx);
	}
	return (false);
}

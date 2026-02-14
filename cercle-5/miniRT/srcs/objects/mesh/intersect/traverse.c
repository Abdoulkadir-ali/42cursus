/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_traverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	intersect_init_ctx(t_trace_ctx *ctx, t_hit *hit)
{
	ctx->top = 0;
	ctx->node_idx = 0;
	ctx->best_tri = -1;
	hit->t = MAX_VALUE;
	ctx->best_t = hit->t;
	ctx->stack[ctx->top++] = 0;
}

static void	process_leaf(t_mesh *mesh, t_mbvh_node *node, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_leaf_ctx	leaf;
	int			i;
	int			*idx;

	i = 0;
	while (i < node->count)
	{
		leaf.tri = node->left_or_first + i;
		idx = &mesh->bvh_indices[leaf.tri * 3];
		leaf.v[0] = mesh->vertices[idx[0]];
		leaf.v[1] = mesh->vertices[idx[1]];
		leaf.v[2] = mesh->vertices[idx[2]];
		if (intersect_triangle_fast(ray, leaf.v, &leaf.t, &leaf.uv)
			&& leaf.t < ctx->best_t)
		{
			ctx->best_t = leaf.t;
			ctx->best_tri = leaf.tri;
			ctx->best_uv = leaf.uv;
		}
		i++;
	}
}

static void	push_mesh_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_child_ctx	child;

	child.left_idx = node_idx + 1;
	child.right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	child.hit_l = aabb_intersect_fast(&mesh->bvh_nodes[child.left_idx].bbox,
			ray, &child.tl_min, &child.tl_max);
	child.hit_r = aabb_intersect_fast(&mesh->bvh_nodes[child.right_idx].bbox,
			ray, &child.tr_min, &child.tr_max);
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

static void	process_node(t_mesh *mesh, const t_ray *ray, t_trace_ctx *ctx)
{
	t_mbvh_node	*node;
	double		t_min;
	double		t_max;

	ctx->node_idx = ctx->stack[--ctx->top];
	node = &mesh->bvh_nodes[ctx->node_idx];
	if (!aabb_intersect_fast(&node->bbox, ray, &t_min, &t_max)
		|| t_min >= ctx->best_t)
		return ;
	if (node->count > 0)
		process_leaf(mesh, node, ray, ctx);
	else
		push_mesh_children(mesh, ctx->node_idx, ray, ctx);
}

void	intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
		t_trace_ctx *ctx)
{
	while (ctx->top > 0)
		process_node(mesh, ray, ctx);
}

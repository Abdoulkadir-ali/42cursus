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
#include "profiler.h"

void	intersect_init_ctx(t_trace_ctx *ctx, t_hit *hit)
{
	ctx->top = 0;
	ctx->node_idx = 0;
	ctx->best_tri = -1;
	hit->t = MAX_VALUE;
	ctx->best_t = hit->t;
}

static void	process_mesh_leaf(t_mesh *mesh, t_mbvh_node *node, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_leaf_ctx	leaf;
	int			i;

	i = 0;
	while (i < node->count)
	{
		PROF_INC(g_mesh_tri_tests);
		leaf.tri = node->left_or_first + i;
		if (intersect_tri_precomp(ray, &mesh->tri_cache[leaf.tri],
				&leaf.t, &leaf.uv)
			&& leaf.t < ctx->best_t)
		{
			ctx->best_t = leaf.t;
			ctx->best_tri = leaf.tri;
			ctx->best_uv = leaf.uv;
		}
		i++;
	}
}

static int	pick_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_child_ctx	c;

	c.left_idx = node_idx + 1;
	c.right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	c.hit_l = aabb_intersect_fast(&mesh->bvh_nodes[c.left_idx].bbox,
			ray, &c.tl_min, &c.tl_max);
	c.hit_r = aabb_intersect_fast(&mesh->bvh_nodes[c.right_idx].bbox,
			ray, &c.tr_min, &c.tr_max);
	if (c.hit_l && c.tl_min >= ctx->best_t)
		c.hit_l = false;
	if (c.hit_r && c.tr_min >= ctx->best_t)
		c.hit_r = false;
	if (c.hit_l && c.hit_r)
	{
		if (c.tl_min > c.tr_min)
		{
			ctx->stack[ctx->top++] = c.left_idx;
			return (c.right_idx);
		}
		ctx->stack[ctx->top++] = c.right_idx;
		return (c.left_idx);
	}
	if (c.hit_l)
		return (c.left_idx);
	if (c.hit_r)
		return (c.right_idx);
	return (-1);
}

void	intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_mbvh_node	*node;
	int			node_idx;

	node_idx = 0;
	while (1)
	{
		PROF_INC(g_mesh_aabb_tests);
		node = &mesh->bvh_nodes[node_idx];
		if (node->count > 0)
		{
			process_mesh_leaf(mesh, node, ray, ctx);
			if (ctx->top == 0)
				return ;
			node_idx = ctx->stack[--ctx->top];
			continue ;
		}
		node_idx = pick_children(mesh, node_idx, ray, ctx);
		if (node_idx < 0)
		{
			if (ctx->top == 0)
				return ;
			node_idx = ctx->stack[--ctx->top];
		}
	}
}

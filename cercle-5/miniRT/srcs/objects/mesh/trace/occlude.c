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

static int	pick_occ_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_occ_ctx *ctx)
{
	t_occ_child	c;

	c.left_idx = node_idx + 1;
	c.right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	c.hit_l = aabb_intersect_fast(
			&mesh->bvh_nodes[c.left_idx].bbox, ray,
			&c.tl_min, &c.tl_max);
	c.hit_r = aabb_intersect_fast(
			&mesh->bvh_nodes[c.right_idx].bbox, ray,
			&c.tr_min, &c.tr_max);
	if (c.hit_l && c.tl_min >= ctx->dist)
		c.hit_l = false;
	if (c.hit_r && c.tr_min >= ctx->dist)
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

bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist)
{
	t_occ_ctx	ctx;
	t_mbvh_node	*node;
	int			node_idx;
	double		tmin;
	double		tmax;

	if (!mesh || !mesh->bvh_nodes)
		return (false);
	if (!aabb_intersect_fast(&mesh->bvh_nodes[0].bbox, ray, &tmin, &tmax)
		|| tmin >= dist)
		return (false);
	PROF_INC(g_mesh_occ_calls);
	ctx.top = 0;
	ctx.dist = dist;
	node_idx = 0;
	while (1)
	{
		node = &mesh->bvh_nodes[node_idx];
		if (node->count > 0)
		{
			if (leaf_occluded(mesh, node, ray, dist))
				return (true);
			if (ctx.top == 0)
				return (false);
			node_idx = ctx.stack[--ctx.top];
			continue ;
		}
		node_idx = pick_occ_children(mesh, node_idx, ray, &ctx);
		if (node_idx < 0)
		{
			if (ctx.top == 0)
				return (false);
			node_idx = ctx.stack[--ctx.top];
		}
	}
}

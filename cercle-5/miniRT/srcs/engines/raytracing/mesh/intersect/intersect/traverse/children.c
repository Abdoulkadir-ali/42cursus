/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	test_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_child_ctx *c)
{
	c->left_idx = node_idx + 1;
	c->right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	c->hit_l = aabb_intersect_fast(&mesh->bvh_nodes[c->left_idx].bbox,
			ray, &c->tl_min, &c->tl_max);
	c->hit_r = aabb_intersect_fast(&mesh->bvh_nodes[c->right_idx].bbox,
			ray, &c->tr_min, &c->tr_max);
}

int	select_child(t_child_ctx *c, t_trace_ctx *ctx)
{
	if (c->hit_l && c->hit_r)
	{
		if (c->tl_min > c->tr_min)
		{
			ctx->stack[ctx->top++] = c->left_idx;
			return (c->right_idx);
		}
		ctx->stack[ctx->top++] = c->right_idx;
		return (c->left_idx);
	}
	if (c->hit_l)
		return (c->left_idx);
	if (c->hit_r)
		return (c->right_idx);
	return (-1);
}

int	pick_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_trace_ctx *ctx)
{
	t_child_ctx	c;

	test_children(mesh, node_idx, ray, &c);
	c.tl_min = (c.tl_min < 0.0) ? 0.0 : c.tl_min;
	c.tr_min = (c.tr_min < 0.0) ? 0.0 : c.tr_min;
	if (c.hit_l && c.tl_min >= ctx->best_t)
		c.hit_l = false;
	if (c.hit_r && c.tr_min >= ctx->best_t)
		c.hit_r = false;
	return (select_child(&c, ctx));
}

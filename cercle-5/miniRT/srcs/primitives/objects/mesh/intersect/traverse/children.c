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

#include "mesh.h"

void	test_children(t_mesh *mesh, t_index node_idx, const t_ray *ray,
		t_child *c)
{
	c->left_idx = node_idx.i + 1;
	c->right_idx = mesh->bvh_nodes[node_idx.i].left_or_first;
	c->hit_l = aabb_intersect_fast(&mesh->bvh_nodes[c->left_idx].bbox,
			ray, &c->tl_min, &c->tl_max);
	c->hit_r = aabb_intersect_fast(&mesh->bvh_nodes[c->right_idx].bbox,
			ray, &c->tr_min, &c->tr_max);
}

size_t	select_child(t_child *c, t_trace *trace)
{
	if (c->hit_l && c->hit_r)
	{
		if (c->tl_min > c->tr_min)
		{
			trace->stack[trace->top++] = c->left_idx;
			return (c->right_idx);
		}
		trace->stack[trace->top++] = c->right_idx;
		return (c->left_idx);
	}
	if (c->hit_l)
		return (c->left_idx);
	if (c->hit_r)
		return (c->right_idx);
	return (0);
}

size_t	pick_children(t_mesh *mesh, t_index node_idx, const t_ray *ray,
		t_trace *trace)
{
	t_child	c;

	test_children(mesh, node_idx, ray, &c);
	if (c.tl_min < 0.0)
		c.tl_min = 0.0;
	if (c.tr_min < 0.0)
		c.tr_min = 0.0;
	if (c.hit_l && c.tl_min >= trace->best_t)
		c.hit_l = false;
	if (c.hit_r && c.tr_min >= trace->best_t)
		c.hit_r = false;
	return (select_child(&c, trace));
}

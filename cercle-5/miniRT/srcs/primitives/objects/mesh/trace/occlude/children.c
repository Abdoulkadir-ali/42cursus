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

void	test_occ_children(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_occ_child *c)
{
	c->left_idx = node_idx + 1;
	c->right_idx = mesh->bvh_nodes[node_idx].left_or_first;
	c->hit_l = aabb_intersect_fast(&mesh->bvh_nodes[c->left_idx].bbox,
			ray, &c->tl_min, &c->tl_max);
	if (c->hit_l && c->tl_min < 0.0)
		c->tl_min = 0.0;
	c->hit_r = aabb_intersect_fast(&mesh->bvh_nodes[c->right_idx].bbox,
			ray, &c->tr_min, &c->tr_max);
	if (c->hit_r && c->tr_min < 0.0)
		c->tr_min = 0.0;
}

size_t	pick_occ_children(t_mesh *mesh, t_index node_idx, const t_ray *ray,
		t_occ *occ)
{
	t_occ_child	c;

	test_occ_children(mesh, node_idx.i, ray, &c);
	if (c.hit_l && c.tl_min >= occ->dist)
		c.hit_l = false;
	if (c.hit_r && c.tr_min >= occ->dist)
		c.hit_r = false;
	if (c.hit_l && c.hit_r)
	{
		if (c.tl_min > c.tr_min)
		{
			occ->stack[occ->top++] = c.left_idx;
			return (c.right_idx);
		}
		occ->stack[occ->top++] = c.right_idx;
		return (c.left_idx);
	}
	if (c.hit_l)
		return (c.left_idx);
	if (c.hit_r)
		return (c.right_idx);
	return (0);
}

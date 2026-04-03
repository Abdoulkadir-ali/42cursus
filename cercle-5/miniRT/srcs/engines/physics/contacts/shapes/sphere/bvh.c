/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:24:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	sphere_leaf(size_t idx, t_sphere *sp, t_contact_query *q,
				const t_bvh_node *node)
{
	size_t		j;
	t_bvh_ref	ref;
	t_scene		*s;

	s = q->engine->scene;
	j = 0;
	while (j < node->count && q->count < q->max)
	{
		ref = s->bvh->refs[node->left_or_first + j];
		if (ref.type == TYPE_SPHERE && ref.index > idx)
			sphere_vs_sphere(sp, &s->spheres[ref.index], q);
		else if (ref.type == TYPE_MESH)
			sphere_vs_mesh(sp, &s->meshes[ref.index], q);
		j++;
	}
}

/**
 * @brief Traverses the scene BVH to find collisions with a sphere.
 */
void	traverse_sphere_bvh(t_contact_query *qu, size_t idx, t_sphere *sp)
{
	size_t				st[64];
	size_t				top;
	const t_bvh_node	*nd;
	t_scene				*s;

	s = qu->engine->scene;
	top = 0;
	st[top++] = 0;
	while (top > 0 && qu->count < qu->max)
	{
		nd = &s->bvh->nodes[st[--top]];
		if (nd->count > 0)
			sphere_leaf(idx, sp, qu, nd);
		else
		{
			if (aabb_v_sphere(s->bvh->nodes[nd->left_or_first + 1].bbox,
					sp->phys.pos, sqrt(sp->radius_sq)))
				st[top++] = nd->left_or_first + 1;
			if (aabb_v_sphere(s->bvh->nodes[nd->left_or_first].bbox,
					sp->phys.pos, sqrt(sp->radius_sq)))
				st[top++] = nd->left_or_first;
		}
	}
}

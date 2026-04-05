/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:24:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	test_one_ref(t_bvh_phys_ctx *c, t_bvh_ref ref)
{
	t_ref_data	d;
	t_col_pair	p;

	if (ref.type == c->skip_type || ref.type == TYPE_SPHERE
		|| ref.type == TYPE_MESH || ref.type == TYPE_ANIM)
		return ;
	if (!bvh_resolve_ref(c->qu->engine->scene, ref, &d))
		return ;
	if (d.body == c->ba)
		return ;
	p = (t_col_pair){c->sa, &d.shape, c->ba, d.body, c->ta, d.xform};
	if (gjk_make_contact(&p, &c->qu->contacts[c->qu->count]))
		c->qu->count++;
}

static void	process_leaf(t_bvh_phys_ctx *c, const t_bvh_node *nd)
{
	size_t		j;
	t_bvh_ref	ref;
	const t_bvh	*bvh;

	bvh = c->qu->engine->scene->bvh;
	j = 0;
	while (j < nd->count && c->qu->count < c->qu->max)
	{
		ref = bvh->refs[nd->left_or_first + j];
		test_one_ref(c, ref);
		j++;
	}
}

/**
 * @brief Traverses the scene BVH to find cross-type collisions.
 */
void	bvh_query_shapes(t_bvh_phys_ctx *c, t_aabb qa)
{
	size_t				st[128];
	size_t				top;
	const t_bvh_node	*nd;
	const t_bvh			*bvh;

	pthread_rwlock_rdlock(&c->qu->engine->scene->bvh_lock);
	bvh = c->qu->engine->scene->bvh;
	if (!bvh)
	{
		pthread_rwlock_unlock(&c->qu->engine->scene->bvh_lock);
		return ;
	}
	top = 0;
	st[top++] = 0;
	while (top > 0 && c->qu->count < c->qu->max)
	{
		nd = &bvh->nodes[st[--top]];
		if (nd->count > 0)
			process_leaf(c, nd);
		else if (top < 126)
		{
			if (aabb_overlap(bvh->nodes[nd->left_or_first + 1].bbox, qa))
				st[top++] = nd->left_or_first + 1;
			if (aabb_overlap(bvh->nodes[nd->left_or_first].bbox, qa))
				st[top++] = nd->left_or_first;
		}
	}
	pthread_rwlock_unlock(&c->qu->engine->scene->bvh_lock);
}

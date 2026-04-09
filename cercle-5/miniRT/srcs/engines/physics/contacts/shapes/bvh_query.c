/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:31:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	test_one_ref(t_bvh_phys_ctx *c, t_bvh_ref ref)
{
	t_ref_data	d;
	t_col_pair	p;

	if (ref.type == TYPE_MESH || ref.type == TYPE_ANIM)
		return ;
	if (ref.type <= c->skip_type)
		return ;
	if (!bvh_resolve_ref(c->qu->engine->scene, ref, &d))
		return ;
	if (d.body == c->ba)
		return ;
	p = (t_col_pair){c->sa, &d.shape, c->ba, d.body, c->ta, d.xform};
	if (gjk_make_contact(&p, &c->qu->contacts[c->qu->count]))
		c->qu->count++;
}

static void	process_leaf(t_bvh_phys_ctx *c, const t_bvh *bvh,
				const t_bvh_node *nd)
{
	size_t		j;
	t_bvh_ref	ref;

	j = 0;
	while (j < nd->count && c->qu->count < c->qu->max)
	{
		ref = bvh->refs[nd->left_or_first + j];
		test_one_ref(c, ref);
		j++;
	}
}

static const t_bvh	*get_locked_bvh(t_scene *s)
{
	const t_bvh	*v;

	pthread_rwlock_rdlock(&s->bvh_lock);
	v = s->bvh;
	if (!v || !v->nodes || !v->refs)
	{
		pthread_rwlock_unlock(&s->bvh_lock);
		return (NULL);
	}
	return (v);
}

static void	traverse_bvh_node(t_bvh_phys_ctx *c, const t_bvh *v,
				size_t *st, t_aabb qa)
{
	size_t				top;
	size_t				nd_idx;
	const t_bvh_node	*nd;

	top = 0;
	st[top++] = 0;
	while (top > 0 && c->qu->count < c->qu->max)
	{
		nd_idx = st[--top];
		nd = &v->nodes[nd_idx];
		if (nd->count > 0)
			process_leaf(c, v, nd);
		else if (top < 126)
		{
			if (aabb_overlap(v->nodes[nd->left_or_first].bbox, qa))
				st[top++] = nd->left_or_first;
			if (aabb_overlap(v->nodes[nd_idx + 1].bbox, qa))
				st[top++] = nd_idx + 1;
		}
	}
}

void	bvh_query_shapes(t_bvh_phys_ctx *c, t_aabb qa)
{
	size_t				st[128];
	const t_bvh			*v;

	v = get_locked_bvh(c->qu->engine->scene);
	if (!v)
		return ;
	traverse_bvh_node(c, v, st, qa);
	pthread_rwlock_unlock(&c->qu->engine->scene->bvh_lock);
}

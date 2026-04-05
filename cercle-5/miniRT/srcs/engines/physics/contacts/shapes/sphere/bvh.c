/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 22:02:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	sphere_leaf(t_contact_query *q, size_t idx, t_sphere *sp,
				const t_bvh_node *node)
{
	size_t		j;
	t_bvh_ref	ref;
	t_scene		*s;
	const t_bvh	*bvh;

	s = q->engine->scene;
	bvh = s->bvh;
	j = -1;
	while (++j < node->count && q->count < q->max)
	{
		ref = bvh->refs[node->left_or_first + j];
		if (ref.type == TYPE_SPHERE && ref.index > idx)
			sphere_vs_sphere(sp, &s->spheres[ref.index], q);
		else if (ref.type == TYPE_MESH)
			sphere_vs_mesh(sp, &s->meshes[ref.index], q);
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

static void	push_sphere_children(const t_bvh *v, const t_bvh_node *nd,
				t_sphere *sp, size_t *st, size_t *top)
{
	double	r;

	r = sqrt(sp->radius_sq);
	if (aabb_v_sphere(v->nodes[nd->left_or_first + 1].bbox,
			sp->phys.pos, r))
		st[(*top)++] = nd->left_or_first + 1;
	if (aabb_v_sphere(v->nodes[nd->left_or_first].bbox,
			sp->phys.pos, r))
		st[(*top)++] = nd->left_or_first;
}

void	traverse_sphere_bvh(t_contact_query *q, size_t idx, t_sphere *sp)
{
	size_t				st[128];
	size_t				top;
	const t_bvh_node	*nd;
	const t_bvh			*v;

	v = get_locked_bvh(q->engine->scene);
	if (!v)
		return ;
	top = 0;
	st[top++] = 0;
	while (top > 0 && q->count < q->max)
	{
		nd = &v->nodes[st[--top]];
		if (nd->count > 0)
			sphere_leaf(q, idx, sp, nd);
		else if (top < 126)
			push_sphere_children(v, nd, sp, st, &top);
	}
	pthread_rwlock_unlock(&q->engine->scene->bvh_lock);
}

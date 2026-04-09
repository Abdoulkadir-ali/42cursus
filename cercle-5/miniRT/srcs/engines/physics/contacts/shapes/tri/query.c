/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	tri_gjk_vs_planes(t_contact_query *qu, t_tri_shape *tr,
		t_gjk_shape *sa)
{
	t_col_pair	p;
	size_t		pi;

	p = (t_col_pair){sa, NULL, &tr->phys, NULL, &tr->xform, NULL};
	pi = 0;
	while (pi < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		qu->count += gjk_vs_plane(&p, &qu->engine->scene->planes[pi],
				&qu->contacts[qu->count]);
		pi++;
	}
}

static void	test_tri_pair(t_contact_query *qu, t_col_pair *p)
{
	if (aabb_overlap(tri_shape_aabb((t_tri_shape *)p->sa->data),
			tri_shape_aabb((t_tri_shape *)p->sb->data)))
	{
		if (gjk_make_contact(p, &qu->contacts[qu->count]))
			qu->count++;
	}
}

static void	tri_vs_tris(t_contact_query *qu, t_tri_shape *tr, size_t idx)
{
	size_t		p;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_tri_shape	*other;

	sa = init_gjk_shape(tr, gjk_support_tri, tr->phys.pos);
	p = idx + 1;
	while (p < qu->engine->scene->tri_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->tris[p];
		sb = init_gjk_shape(other, gjk_support_tri, other->phys.pos);
		pair = (t_col_pair){&sa, &sb, &tr->phys, &other->phys, &tr->xform,
			&other->xform};
		test_tri_pair(qu, &pair);
		p++;
	}
}

size_t	query_tri(t_contact_query *qu, size_t idx)
{
	t_tri_shape		*tr;
	t_gjk_shape		sa;
	t_bvh_phys_ctx	ctx;

	tr = &qu->engine->scene->tris[idx];
	if (tr->phys.is_static)
		return (qu->count);
	sa = init_gjk_shape(tr, gjk_support_tri, tr->phys.pos);
	tri_gjk_vs_planes(qu, tr, &sa);
	tri_vs_tris(qu, tr, idx);
	ctx = (t_bvh_phys_ctx){qu, &sa, &tr->phys, &tr->xform, TYPE_TRI};
	bvh_query_shapes(&ctx, tri_shape_aabb(tr));
	return (qu->count);
}

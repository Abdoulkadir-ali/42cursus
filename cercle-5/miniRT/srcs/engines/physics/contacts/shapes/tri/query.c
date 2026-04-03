/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:45:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

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

	sa = (t_gjk_shape){tr, gjk_support_tri, tr->phys.pos};
	p = idx + 1;
	while (p < qu->engine->scene->tri_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->tris[p];
		sb = (t_gjk_shape){other, gjk_support_tri, other->phys.pos};
		pair = (t_col_pair){&sa, &sb, &tr->phys, &other->phys, &tr->xform,
			&other->xform};
		test_tri_pair(qu, &pair);
		p++;
	}
}

size_t	query_tri(t_contact_query *qu, size_t idx)
{
	t_tri_shape	*tr;
	t_gjk_shape	sa;

	tr = &qu->engine->scene->tris[idx];
	if (tr->phys.is_static)
		return (qu->count);
	tri_vs_all_planes(qu, tr);
	tri_vs_tris(qu, tr, idx);
	sa = (t_gjk_shape){tr, gjk_support_tri, tr->phys.pos};
	query_shapes(qu, &sa, &tr->phys, &tr->xform);
	return (qu->count);
}

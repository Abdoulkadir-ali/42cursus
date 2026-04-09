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

static void	rect_gjk_vs_planes(t_contact_query *qu, t_rect *rc,
		t_gjk_shape *sa)
{
	t_col_pair	p;
	size_t		pi;

	p = (t_col_pair){sa, NULL, &rc->phys, NULL, &rc->transform, NULL};
	pi = 0;
	while (pi < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		qu->count += gjk_vs_plane(&p, &qu->engine->scene->planes[pi],
				&qu->contacts[qu->count]);
		pi++;
	}
}

static void	test_rect_pair(t_contact_query *qu, t_col_pair *p)
{
	if (aabb_overlap(rect_aabb((t_rect *)p->sa->data),
			rect_aabb((t_rect *)p->sb->data)))
	{
		if (gjk_make_contact(p, &qu->contacts[qu->count]))
			qu->count++;
	}
}

static void	rect_vs_rects(t_contact_query *qu, t_rect *rc, size_t idx)
{
	size_t		p;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_rect		*other;

	sa = init_gjk_shape(rc, gjk_support_rect, rc->phys.pos);
	p = idx + 1;
	while (p < qu->engine->scene->rect_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->rects[p];
		sb = init_gjk_shape(other, gjk_support_rect, other->phys.pos);
		pair = (t_col_pair){&sa, &sb, &rc->phys, &other->phys,
			&rc->transform, &other->transform};
		test_rect_pair(qu, &pair);
		p++;
	}
}

size_t	query_rect(t_contact_query *qu, size_t idx)
{
	t_rect			*rc;
	t_gjk_shape		sa;
	t_bvh_phys_ctx	ctx;

	rc = &qu->engine->scene->rects[idx];
	if (rc->phys.is_static)
		return (qu->count);
	sa = init_gjk_shape(rc, gjk_support_rect, rc->phys.pos);
	rect_gjk_vs_planes(qu, rc, &sa);
	rect_vs_rects(qu, rc, idx);
	ctx = (t_bvh_phys_ctx){qu, &sa, &rc->phys, &rc->transform, TYPE_RECT};
	bvh_query_shapes(&ctx, rect_aabb(rc));
	return (qu->count);
}

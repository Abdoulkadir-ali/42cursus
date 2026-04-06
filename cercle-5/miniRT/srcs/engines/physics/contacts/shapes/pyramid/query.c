/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	test_pyramid_pair(t_contact_query *qu, t_col_pair *p)
{
	if (aabb_overlap(pyramid_aabb((t_pyramid *)p->sa->data),
			pyramid_aabb((t_pyramid *)p->sb->data)))
	{
		if (gjk_make_contact(p, &qu->contacts[qu->count]))
			qu->count++;
	}
}

static void	pyramid_vs_pyramids(t_contact_query *qu, t_pyramid *py, size_t idx)
{
	size_t		p;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	t_col_pair	pair;

	sa = init_gjk_shape(py, gjk_support_pyramid, py->phys.pos);
	p = idx + 1;
	while (p < qu->engine->scene->pyramid_count && qu->count < qu->max)
	{
		sb = init_gjk_shape(&qu->engine->scene->pyramids[p], gjk_support_pyramid,
			qu->engine->scene->pyramids[p].phys.pos);
		pair = (t_col_pair){&sa, &sb, &py->phys,
			&qu->engine->scene->pyramids[p].phys, &py->transform,
			&qu->engine->scene->pyramids[p].transform};
		test_pyramid_pair(qu, &pair);
		p++;
	}
}

size_t	query_pyramid(t_contact_query *qu, size_t idx)
{
	t_pyramid		*py;
	t_gjk_shape		sa;
	t_bvh_phys_ctx	ctx;

	py = &qu->engine->scene->pyramids[idx];
	if (py->phys.is_static)
		return (qu->count);
	pyramid_vs_planes(qu, py);
	pyramid_vs_pyramids(qu, py, idx);
	sa = init_gjk_shape(py, gjk_support_pyramid, py->phys.pos);
	ctx = (t_bvh_phys_ctx){qu, &sa, &py->phys, &py->transform, TYPE_PYRAMID};
	bvh_query_shapes(&ctx, pyramid_aabb(py));
	return (qu->count);
}

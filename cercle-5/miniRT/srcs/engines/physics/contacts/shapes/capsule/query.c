/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:24:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	capsule_vs_capsules(t_contact_query *qu, t_col_pair *p, size_t idx)
{
	size_t		pi;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_capsule	*other;

	pi = idx + 1;
	while (pi < qu->engine->scene->capsule_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->capsules[pi];
		if (aabb_overlap(capsule_aabb((t_capsule *)p->sa->data),
				capsule_aabb(other)))
		{
			sb = (t_gjk_shape){other, gjk_support_capsule, other->phys.pos};
			pair = (t_col_pair){p->sa, &sb, p->ba, &other->phys,
				p->ta, &other->transform};
			if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
				qu->count++;
		}
		pi++;
	}
}

size_t	query_capsule(t_contact_query *qu, size_t idx)
{
	t_capsule	*cap;
	t_gjk_shape	sa;
	t_col_pair	p;
	size_t		pi;

	cap = &qu->engine->scene->capsules[idx];
	if (cap->phys.is_static)
		return (qu->count);
	sa = (t_gjk_shape){cap, gjk_support_capsule, cap->phys.pos};
	p = (t_col_pair){&sa, NULL, &cap->phys, NULL, &cap->transform, NULL};
	pi = 0;
	while (pi < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		qu->count += gjk_vs_plane(&p, &qu->engine->scene->planes[pi],
				&qu->contacts[qu->count]);
		pi++;
	}
	capsule_vs_capsules(qu, &p, idx);
	query_shapes(qu, &sa, &cap->phys, &cap->transform);
	return (qu->count);
}

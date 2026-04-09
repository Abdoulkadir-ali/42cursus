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

static void	capsule_vs_capsules(t_contact_query *qu, t_col_pair *p, size_t idx)
{
	size_t		pi;
	t_capsule	*self;
	t_capsule	*other;

	self = (t_capsule *)p->sa->data;
	pi = idx + 1;
	while (pi < qu->engine->scene->capsule_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->capsules[pi];
		if (aabb_overlap(capsule_aabb(self), capsule_aabb(other)))
			analytic_capsule_capsule(qu, self, other);
		pi++;
	}
}

size_t	query_capsule(t_contact_query *qu, size_t idx)
{
	t_capsule		*cap;
	t_gjk_shape		sa;
	t_col_pair		p;
	size_t			pi;
	t_bvh_phys_ctx	ctx;

	cap = &qu->engine->scene->capsules[idx];
	if (cap->phys.is_static)
		return (qu->count);
	sa = init_gjk_shape(cap, gjk_support_capsule, cap->phys.center);
	p = (t_col_pair){&sa, NULL, &cap->phys, NULL, &cap->transform, NULL};
	pi = 0;
	while (pi < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		qu->count += gjk_vs_plane(&p, &qu->engine->scene->planes[pi],
				&qu->contacts[qu->count]);
		pi++;
	}
	capsule_vs_capsules(qu, &p, idx);
	ctx = (t_bvh_phys_ctx){qu, &sa, &cap->phys, &cap->transform, TYPE_CAPSULE};
	bvh_query_shapes(&ctx, capsule_aabb(cap));
	return (qu->count);
}

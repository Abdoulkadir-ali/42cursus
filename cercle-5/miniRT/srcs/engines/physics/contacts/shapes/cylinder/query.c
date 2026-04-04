/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 19:28:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

static void	cylinder_vs_cylinders(t_contact_query *qu, t_col_pair *p,
		size_t idx)
{
	size_t		pi;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_cylinder	*other;

	pi = idx + 1;
	while (pi < qu->engine->scene->cylinder_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->cylinders[pi];
		if (aabb_overlap(cylinder_aabb((t_cylinder *)p->sa->data),
				cylinder_aabb(other)))
		{
			sb = (t_gjk_shape){other, gjk_support_cylinder, other->phys.pos};
			pair = (t_col_pair){p->sa, &sb, p->ba, &other->phys, p->ta,
				&other->transform};
			if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
				qu->count++;
		}
		pi++;
	}
}

size_t	query_cylinder(t_contact_query *qu, size_t idx)
{
	t_cylinder	*cy;
	t_gjk_shape	sa;
	t_col_pair	p;

	cy = &qu->engine->scene->cylinders[idx];
	if (cy->phys.is_static)
		return (qu->count);
	sa = (t_gjk_shape){cy, gjk_support_cylinder, cy->phys.pos};
	p = (t_col_pair){&sa, NULL, &cy->phys, NULL, &cy->transform, NULL};
	cylinder_vs_all_planes(qu, &p);
	cylinder_vs_cylinders(qu, &p, idx);
	loop_boxes(qu, &sa, &cy->phys, &cy->transform);
	loop_capsules(qu, &sa, &cy->phys, &cy->transform);
	loop_rects(qu, &sa, &cy->phys, &cy->transform);
	loop_tris(qu, &sa, &cy->phys, &cy->transform);
	loop_pyramids(qu, &sa, &cy->phys, &cy->transform);
	return (qu->count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:04:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	rect_vs_others(t_physics *phys, int idx, t_rect *rc, t_aabb raabb,
		t_contact *c, int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;
	t_scene		*s;
	t_aabb		pb;

	s = phys->scene;
	sa = (t_gjk_shape){s, idx};
	p = idx + 1;
	while (p < (int)s->primitives.count && count < max)
	{
		pb = get_primitive_aabb_soa(&s->primitives, p);
		if (s->primitives.types[p] == PRIM_RECT && aabb_overlap(&raabb, &pb))
		{
			sb = (t_gjk_shape){s, p};
			count += gjk_make_contact(&sa, &sb, idx, p, &c[count]);
		}
		p++;
	}
	(void)rc;
	return (prim_others_contacts(phys, idx, raabb, &sa, c, count, max));
}

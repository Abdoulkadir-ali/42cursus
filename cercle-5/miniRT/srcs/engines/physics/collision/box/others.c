/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:05:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	box_vs_others(t_physics *phys, int idx, t_box *bx, t_aabb baabb, t_contact *c,
		int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;
	t_scene		*s;
	t_aabb		pb;

	(void)bx;
	s = phys->scene;
	sa = (t_gjk_shape){s, idx};
	p = idx + 1;
	while (p < (int)s->primitives.count && count < max)
	{
		pb = get_primitive_aabb_soa(&s->primitives, p);
		if (s->primitives.types[p] == PRIM_BOX && aabb_overlap(&baabb, &pb))
		{
			sb = (t_gjk_shape){s, p};
			count += gjk_make_contact(&sa, &sb, idx, p, &c[count]);
		}
		p++;
	}
	return (prim_others_contacts(phys, idx, baabb, &sa, c, count, max));
}

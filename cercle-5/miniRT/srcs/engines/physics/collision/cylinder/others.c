/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:17:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	cyl_vs_others(t_physics *phys, int idx, t_cylinder *cy, t_aabb cyaabb,
		t_contact *c, int count, int max)
{
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;
	t_scene		*s;
	t_aabb		pb;

	s = phys->scene;
	sa = (t_gjk_shape){phys->scene, idx};
	p = idx + 1;
	while (p < (int)s->primitives.count && count < max)
	{
		pb = get_primitive_aabb_soa(&s->primitives, p);
		if (s->primitives.types[p] == PRIM_CYLINDER && aabb_overlap(&cyaabb, &pb))
		{
			sb = (t_gjk_shape){phys->scene, p};
			count += gjk_make_contact(&sa, &sb, idx, p, &c[count]);
		}
		p++;
	}
	(void)cy;
	return (prim_others_contacts(phys, idx, cyaabb, &sa, c, count, max));
}

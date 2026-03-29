/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:23:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	prim_others_contacts(t_physics *phys, int idx, t_aabb aabb,
		t_gjk_shape *sa, t_contact *c, int count, int max)
{
	(void)sa;
	int			p;
	t_scene		*s;
	t_aabb		pb;

	s = phys->scene;
	p = idx;
	while (++p < (int)s->primitives.count && count < max)
	{
		if (s->primitives.is_static[p] && s->primitives.is_static[idx])
			continue ;
		if (s->primitives.types[p] == PRIM_PLANE)
			continue ;
		pb = get_primitive_aabb_soa(&s->primitives, p);
		if (aabb_overlap(&aabb, &pb))
			count += gjk_make_contact(phys, idx, p, &c[count]);
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_tri(t_physics *phys, int idx, t_contact *c, int count, int max)
{
	t_aabb		ta;
	t_gjk_shape	sa;
	t_scene		*s;

	s = phys->scene;
	if (s->primitives.is_static[idx])
		return (count);
	ta = get_tri_aabb_soa(&s->tri_soa, idx);
	sa = (t_gjk_shape){s, idx};
	count = prim_plane_contacts(phys, idx, &sa, c, count, max);
	return (prim_others_contacts(phys, idx, ta, &sa, c, count, max));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:09:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_capsule(t_physics *phys, int idx, t_contact *c, int count, int max)
{
	t_aabb		ca;
	t_gjk_shape	sa;
	t_scene		*s;

	s = phys->scene;
	if (s->primitives.is_static[idx])
		return (count);
	ca = get_primitive_aabb_soa(&s->primitives, idx);
	init_gjk_shape(&sa, phys, idx);
	count = prim_plane_contacts(phys, idx, c, count, max);
	return (prim_others_contacts(phys, idx, ca, &sa, c, count, max));
}

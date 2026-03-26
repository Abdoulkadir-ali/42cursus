/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

int	query_capsule(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_capsule	*cap;
	t_aabb		ca;
	t_gjk_shape	sa;

	cap = &s->capsules[idx];
	if (cap->phys.is_static)
		return (count);
	ca = capsule_aabb(cap);
	sa = (t_gjk_shape){cap, gjk_support_capsule, cap->phys.center};
	count = capsule_plane_contacts(s, cap, &sa, c, count, max);
	return (cap_vs_others(s, idx, cap, ca, c, count, max));
}

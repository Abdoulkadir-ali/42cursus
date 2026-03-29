/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_capsule	unpack_capsule(const t_primitive_array *p, int i)
{
	t_capsule	ca;
	t_vec3		pos;
	t_vec3		axis;

	ft_memset(&ca, 0, sizeof(ca));
	if (i < 0 || (size_t)i >= p->count)
		return (ca);
	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	ca.a = pos;
	ca.b = vec3_add(pos, vec3_scale(axis, p->heights[i]));
	ca.radius = p->radii[i];
	ca.mat_idx = p->mat_ids[i];
	return (ca);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:45:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	physics_apply_impulse(t_physics *phys, int prim_idx, t_vec3 impulse)
{
	t_physics_soa	*s;
	int				pb;

	if (!phys || !phys->soa || !phys->scene)
		return ;
	s = phys->soa;
	if (prim_idx < 0 || (size_t)prim_idx >= phys->scene->primitives.count)
		return ;
	pb = phys->scene->primitives.phys_idx[prim_idx];
	if (pb < 0 || (size_t)pb >= s->count || s->is_static[pb])
		return ;
	s->hot.vx[pb] += (float)(impulse.x * s->inv_mass[pb]);
	s->hot.vy[pb] += (float)(impulse.y * s->inv_mass[pb]);
	s->hot.vz[pb] += (float)(impulse.z * s->inv_mass[pb]);
}


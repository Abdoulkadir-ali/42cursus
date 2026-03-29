/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:24:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	physics_shoot_ray(t_physics *phys, t_ray ray, double impulse)
{
	t_physics_soa	*s;
	int				pb;

	if (!phys || !phys->soa)
		return ;
	s = phys->soa;
	pb = -1;
	if (pb < 0 || s->is_static[pb])
		return ;
	s->hot.vx[pb] += (float)(ray.direction.x * impulse * s->inv_mass[pb]);
	s->hot.vy[pb] += (float)(ray.direction.y * impulse * s->inv_mass[pb]);
	s->hot.vz[pb] += (float)(ray.direction.z * impulse * s->inv_mass[pb]);
}


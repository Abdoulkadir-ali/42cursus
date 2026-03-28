/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_vec3	point_vel(t_physics *p, int body_idx, t_vec3 r)
{
	t_physics_soa	*s;

	if (body_idx < 0 || !p || !p->soa)
		return (vec3(0, 0, 0));
	s = p->soa;
	return (vec3_add(vec3(s->vx[body_idx], s->vy[body_idx], s->vz[body_idx]),
			vec3_cross(vec3(s->ang_vx[body_idx], s->ang_vy[body_idx],
					s->ang_vz[body_idx]), r)));
}

double	ang_term(t_physics *p, int body_idx, t_vec3 r, t_vec3 dir, double inv_m)
{
	t_vec3			rxd;
	t_physics_soa	*s;

	if (body_idx < 0 || !p || !p->soa || inv_m < 1e-9)
		return (0.0);
	s = p->soa;
	rxd = vec3_cross(r, dir);
	return (inv_m * (rxd.x * rxd.x * s->inv_ix[body_idx]
			+ rxd.y * rxd.y * s->inv_iy[body_idx]
			+ rxd.z * rxd.z * s->inv_iz[body_idx]));
}

void	apply_solver_torque(t_physics *p, int body_idx, t_vec3 r, t_vec3 imp,
		double inv_m, double sign)
{
	t_vec3			torque;
	t_vec3			dw;
	t_physics_soa	*s;

	if (body_idx < 0 || !p || !p->soa)
		return ;
	s = p->soa;
	torque = vec3_cross(r, vec3_scale(imp, sign));
	dw.x = torque.x * inv_m * s->inv_ix[body_idx];
	dw.y = torque.y * inv_m * s->inv_iy[body_idx];
	dw.z = torque.z * inv_m * s->inv_iz[body_idx];
	s->ang_vx[body_idx] += dw.x;
	s->ang_vy[body_idx] += dw.y;
	s->ang_vz[body_idx] += dw.z;
}

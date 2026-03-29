/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impulse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:36:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	apply_impulse(t_physics *p, t_contact *ct, t_vec3 imp,
		double inv_a, double inv_b)
{
	t_physics_soa	*s;
	int				pa;
	int				pb;

	s = p->soa;
	pa = p->scene->primitives.phys_idx[ct->idx_a];
	pb = p->scene->primitives.phys_idx[ct->idx_b];
	if (pa >= 0 && inv_a > 1e-9)
	{
		s->hot.vx[pa] -= (float)(imp.x * inv_a);
		s->hot.vy[pa] -= (float)(imp.y * inv_a);
		s->hot.vz[pa] -= (float)(imp.z * inv_a);
		apply_solver_torque(p, pa, ct->ra, imp, inv_a, -1.0);
	}
	if (pb >= 0 && inv_b > 1e-9)
	{
		s->hot.vx[pb] += (float)(imp.x * inv_b);
		s->hot.vy[pb] += (float)(imp.y * inv_b);
		s->hot.vz[pb] += (float)(imp.z * inv_b);
		apply_solver_torque(p, pb, ct->rb, imp, inv_b, 1.0);
	}
}

double	solve_one_velocity(t_physics *p, t_contact *ct, double inv_a,
		double inv_b)
{
	t_vec3	rv;
	double	j[2];
	double	vn;
	double	denom;
	int		pa_pb[2];

	pa_pb[0] = p->scene->primitives.phys_idx[ct->idx_a];
	pa_pb[1] = p->scene->primitives.phys_idx[ct->idx_b];
	rv = vec3_sub(point_vel(p, pa_pb[1], ct->rb),
			point_vel(p, pa_pb[0], ct->ra));
	vn = vec3_dot(rv, ct->normal);
	if (vn < 0.0)
	{
		denom = inv_a + inv_b + ang_term(p, pa_pb[0], ct->ra, ct->normal, inv_a)
			+ ang_term(p, pa_pb[1], ct->rb, ct->normal, inv_b);
		if (denom < 1e-9)
			return (0.0);
		j[1] = 0.0;
		if (vn < -0.01)
			j[1] = ct->restitution;
		j[0] = -(1.0 + j[1]) * vn / denom;
		apply_impulse(p, ct, vec3_scale(ct->normal, j[0]), inv_a, inv_b);
		rv = vec3_sub(point_vel(p, pa_pb[1], ct->rb),
				point_vel(p, pa_pb[0], ct->ra));
		apply_friction(p, ct, inv_a, inv_b, rv);
		return (j[0]);
	}
	return (0.0);
}

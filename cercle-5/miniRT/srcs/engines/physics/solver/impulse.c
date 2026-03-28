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

static void	apply_impulse(t_physics *p, t_contact *ct, t_vec3 imp, double inv_a, double inv_b)
{
	t_physics_soa	*s = p->soa;
	int				pa = ct->scene->primitives.phys_idx[ct->idx_a];
	int				pb = ct->scene->primitives.phys_idx[ct->idx_b];

	if (pa >= 0 && inv_a > 1e-9)
	{
		s->vx[pa] -= (float)(imp.x * inv_a);
		s->vy[pa] -= (float)(imp.y * inv_a);
		s->vz[pa] -= (float)(imp.z * inv_a);
		apply_solver_torque(p, pa, ct->ra, imp, inv_a, -1.0);
	}
	if (pb >= 0 && inv_b > 1e-9)
	{
		s->vx[pb] += (float)(imp.x * inv_b);
		s->vy[pb] += (float)(imp.y * inv_b);
		s->vz[pb] += (float)(imp.z * inv_b);
		apply_solver_torque(p, pb, ct->rb, imp, inv_b, 1.0);
	}
}

double	solve_one_velocity(t_physics *p, t_contact *ct, double inv_a, double inv_b)
{
	t_vec3	rv;
	double	vn;
	double	denom;
	double	j;
	double	e;
	int		pa = ct->scene->primitives.phys_idx[ct->idx_a];
	int		pb = ct->scene->primitives.phys_idx[ct->idx_b];

	rv = vec3_sub(point_vel(p, pb, ct->rb), point_vel(p, pa, ct->ra));
	vn = vec3_dot(rv, ct->normal);
	if (vn < 0.0)
	{
		denom = (inv_a + inv_b + ang_term(p, pa, ct->ra, ct->normal, inv_a)
				+ ang_term(p, pb, ct->rb, ct->normal, inv_b));
		if (denom < 1e-9)
			return (0.0);
		e = (vn < -0.01) ? ct->restitution : 0.0;
		j = -(1.0 + e) * vn / denom;
		apply_impulse(p, ct, vec3_scale(ct->normal, j), inv_a, inv_b);
		rv = vec3_sub(point_vel(p, pb, ct->rb), point_vel(p, pa, ct->ra));
		apply_friction(ct, inv_a, inv_b, rv);
		return (j);
	}
	return (0.0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 12:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	update_vel(t_contact *ct, double ia, double ib, double dj)
{
	t_vec3	imp;

	imp = vec3_scale(ct->normal, dj);
	if (ct->a && ia > 0.0)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity, vec3_scale(ct->normal,
					dj * ia));
		apply_phys_torque(ct->a, ct->ra, imp, -1.0);
	}
	if (ct->b && ib > 0.0)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(ct->normal,
					dj * ib));
		apply_phys_torque(ct->b, ct->rb, imp, 1.0);
	}
}

static void	apply_slop_and_j(t_contact *ct, t_physic_engine *en, double vn,
				double denom)
{
	double	e;
	double	j;
	double	old_accum;

	e = 0.0;
	if (vn < -en->settings.restitution_slop)
		e = ct->restitution;
	j = -(1.0 + e) * vn / denom;
	old_accum = ct->accum_n;
	ct->accum_n = old_accum + j;
	if (ct->accum_n < 0.0)
		ct->accum_n = 0.0;
	if (ct->accum_n > 1e-6)
	{
		wake_body(ct->a);
		wake_body(ct->b);
	}
	update_vel(ct, get_inv_mass(ct->a), get_inv_mass(ct->b),
		ct->accum_n - old_accum);
	phys_heat_collision(ct, ct->accum_n - old_accum, e);
	apply_friction(ct, vec3_sub(point_vel(ct->b, ct->rb),
			point_vel(ct->a, ct->ra)), ct->accum_n);
}

void	solve_one_velocity(t_contact *ct, t_physic_engine *en, double ia,
		double ib)
{
	t_vec3	rel_v;
	double	vn;
	double	denom;

	rel_v = vec3_sub(point_vel(ct->b, ct->rb), point_vel(ct->a, ct->ra));
	vn = vec3_dot(rel_v, ct->normal);
	denom = ia + ib + ang_term(ct->a, ct->ra, ct->normal, ia)
		+ ang_term(ct->b, ct->rb, ct->normal, ib);
	if (denom < 1e-9)
		return ;
	apply_slop_and_j(ct, en, vn, denom);
}

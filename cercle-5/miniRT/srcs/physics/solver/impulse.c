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

static void	apply_impulse(t_contact *ct, t_vec3 imp, double inv_a, double inv_b)
{
	if (ct->a && inv_a > 1e-9)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity, vec3_scale(imp, inv_a));
		apply_solver_torque(ct->a, ct->ra, imp, inv_a, -1.0);
	}
	if (ct->b && inv_b > 1e-9)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(imp, inv_b));
		apply_solver_torque(ct->b, ct->rb, imp, inv_b, 1.0);
	}
}

/**
 * @brief Handles main collision response impulses.
 * Returns the computed impulse scalar j for compound torque transfer.
 */
double	solve_one_velocity(t_contact *ct, double inv_a, double inv_b)
{
	t_vec3	rv;
	double	vn;
	double	denom;
	double	j;
	double	e;

	rv = vec3_sub(point_vel(ct->b, ct->rb), point_vel(ct->a, ct->ra));
	vn = vec3_dot(rv, ct->normal);
	if (vn < 0.0)
	{
		denom = (inv_a + inv_b + ang_term(ct->a, ct->ra, ct->normal, inv_a)
				+ ang_term(ct->b, ct->rb, ct->normal, inv_b));
		if (denom < 1e-9)
			return (0.0);
		e = (vn < -RESTITUTION_SLOP) ? ct->restitution : 0.0;
		j = -(1.0 + e) * vn / denom;
		apply_impulse(ct, vec3_scale(ct->normal, j), inv_a, inv_b);
		rv = vec3_sub(point_vel(ct->b, ct->rb), point_vel(ct->a, ct->ra));
		apply_friction(ct, inv_a, inv_b, rv);
		return (j);
	}
	return (0.0);
}

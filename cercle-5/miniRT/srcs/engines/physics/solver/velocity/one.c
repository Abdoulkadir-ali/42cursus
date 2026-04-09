/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Internal helper to update velocities for both bodies.
 */
static void	update_vel(t_contact *ct, double ia, double ib, double j)
{
	t_vec3	imp;

	imp = vec3_scale(ct->normal, j);
	if (ct->a && ia > 0.0)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity, vec3_scale(ct->normal,
					j * ia));
		apply_phys_torque(ct->a, ct->ra, imp, -1.0);
	}
	if (ct->b && ib > 0.0)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(ct->normal,
					j * ib));
		apply_phys_torque(ct->b, ct->rb, imp, 1.0);
	}
}

/**
 * @brief Calculates and applies a single normal impulse for a contact.
 */
void	solve_one_velocity(t_contact *ct, t_physic_engine *en, double ia,
		double ib)
{
	t_vec3	rel_v;
	double	vn;
	double	denom;
	double	e;

	rel_v = vec3_sub(point_vel(ct->b, ct->rb), point_vel(ct->a, ct->ra));
	vn = vec3_dot(rel_v, ct->normal);
	if (vn >= 0.0)
		return ;
	denom = ia + ib + ang_term(ct->a, ct->ra, ct->normal, ia)
		+ ang_term(ct->b, ct->rb, ct->normal, ib);
	if (denom < 1e-9)
		return ;
	e = 0.0;
	if (vn < -en->settings.restitution_slop)
		e = ct->restitution;
	update_vel(ct, ia, ib, -(1.0 + e) * vn / denom);
	apply_friction(ct, ia, ib, vec3_sub(point_vel(ct->b, ct->rb),
			point_vel(ct->a, ct->ra)), -(1.0 + e) * vn / denom);
}

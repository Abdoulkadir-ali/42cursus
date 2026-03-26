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

static void	apply_f_impulse(t_contact *ct, t_vec3 fi, double inv_a, double inv_b)
{
	if (ct->a && inv_a > 1e-9)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity, vec3_scale(fi, inv_a));
		apply_solver_torque(ct->a, ct->ra, fi, inv_a, -1.0);
	}
	if (ct->b && inv_b > 1e-9)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(fi, inv_b));
		apply_solver_torque(ct->b, ct->rb, fi, inv_b, 1.0);
	}
}

/**
 * @brief Handles Coulomb friction impulses at the contact point.
 */
void	apply_friction(t_contact *ct, double inv_a, double inv_b, t_vec3 rel_v)
{
	t_vec3	tangent;
	double	denom;
	double	jt;

	tangent = vec3_sub(rel_v, vec3_scale(ct->normal,
				vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(tangent) <= 1e-6)
		return ;
	tangent = vec3_norm(tangent);
	denom = inv_a + inv_b
		+ ang_term(ct->a, ct->ra, tangent, inv_a)
		+ ang_term(ct->b, ct->rb, tangent, inv_b);
	if (denom < 1e-9)
		return ;
	jt = -vec3_dot(rel_v, tangent) / denom;
	if (jt < 0.0)
		apply_f_impulse(ct, vec3_scale(tangent, jt * ct->friction),
			inv_a, inv_b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Applies rotational impulse (torque) to a physics body.
 * @param i_m_s Precomputed inverse_mass * sign.
 */
void	apply_phys_torque(t_physics_body *b, t_vec3 r, t_vec3 imp, double i_m_s)
{
	t_vec3	torque;
	t_vec3	dw;

	torque = vec3_cross(r, vec3_scale(imp, i_m_s));
	dw.x = torque.x * b->inv_inertia.x;
	dw.y = torque.y * b->inv_inertia.y;
	dw.z = torque.z * b->inv_inertia.z;
	b->angular_velocity = vec3_add(b->angular_velocity, dw);
}

/**
 * @brief Helper to apply friction impulses to both bodies in a contact.
 */
static void	apply_f_imp(t_contact *ct, t_vec3 f_imp, double ia, double ib)
{
	if (ct->a && ia > 0.0)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity, vec3_scale(f_imp, ia));
		apply_phys_torque(ct->a, ct->ra, f_imp, -ia);
	}
	if (ct->b && ib > 0.0)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(f_imp, ib));
		apply_phys_torque(ct->b, ct->rb, f_imp, ib);
	}
}

/**
 * @brief Calculates and applies frictional impulses along the contact tangent.
 */
void	apply_friction(t_contact *ct, double ia, double ib, t_vec3 rel_v)
{
	t_vec3	vt;
	t_vec3	tangent;
	double	denom;
	double	jt;

	vt = vec3_sub(rel_v, vec3_scale(ct->normal, vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt) <= 1e-6)
		return ;
	tangent = vec3_norm(vt);
	denom = ia + ib + ang_term(ct->a, ct->ra, tangent, ia)
		+ ang_term(ct->b, ct->rb, tangent, ib);
	if (denom < 1e-9)
		return ;
	jt = -vec3_dot(rel_v, tangent) / denom;
	if (jt > 0.0)
		jt = 0.0;
	apply_f_imp(ct, vec3_scale(tangent, jt * ct->friction), ia, ib);
}

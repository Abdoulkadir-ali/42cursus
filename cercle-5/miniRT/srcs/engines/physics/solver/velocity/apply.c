/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Applies rotational impulse (torque) to a physics body.
 * @param sign Direction of the impulse for this body (-1 or 1).
 */
void	apply_phys_torque(t_physics_body *b, t_vec3 r, t_vec3 imp, double sign)
{
	t_vec3	torque;
	t_vec3	dw;

	torque = vec3_cross(r, vec3_scale(imp, sign));
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
		apply_phys_torque(ct->a, ct->ra, f_imp, -1.0);
	}
	if (ct->b && ib > 0.0)
	{
		ct->b->velocity = vec3_add(ct->b->velocity, vec3_scale(f_imp, ib));
		apply_phys_torque(ct->b, ct->rb, f_imp, 1.0);
	}
}

/**
 * @brief Calculates and applies frictional impulses along the contact tangent.
 *        Clamped via Coulomb friction cone: |jt| <= friction * j_normal.
 */
void	apply_friction(t_contact *ct, t_vec3 rel_v, double j_normal)
{
	t_vec3	vt;
	t_vec3	tangent;
	double	ia;
	double	ib;
	double	jt;

	ia = get_inv_mass(ct->a);
	ib = get_inv_mass(ct->b);
	vt = vec3_sub(rel_v, vec3_scale(ct->normal, vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt) <= 1e-6)
		return ;
	tangent = vec3_norm(vt);
	jt = -vec3_dot(rel_v, tangent) / (ia + ib + ang_term(ct->a, ct->ra,
				tangent, ia) + ang_term(ct->b, ct->rb, tangent, ib));
	if (jt > 0.0)
		jt = 0.0;
	else if (jt < -ct->friction * j_normal)
		jt = -ct->friction * j_normal;
	apply_f_imp(ct, vec3_scale(tangent, jt), ia, ib);
}

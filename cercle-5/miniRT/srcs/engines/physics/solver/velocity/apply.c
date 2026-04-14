/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 16:41:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Applies rotational impulse (torque) to a physics body.
 *        When orient_r/u/f are set, transforms the torque into the body's
 *        local frame before applying the (diagonal) inertia inverse — this
 *        is the R * I_inv * R^T operation that keeps spinning correct for
 *        rotated boxes and pyramids.
 * @param sign Direction of the impulse for this body (-1 or 1).
 */
void	apply_phys_torque(t_physics_body *b, t_vec3 r, t_vec3 imp, double sign)
{
	t_vec3	torque;
	t_vec3	tl;
	t_vec3	dw;

	torque = vec3_cross(r, vec3_scale(imp, sign));
	if (vec3_mag_sq(b->orient_r) > 1e-9)
	{
		tl.x = vec3_dot(torque, b->orient_r);
		tl.y = vec3_dot(torque, b->orient_u);
		tl.z = vec3_dot(torque, b->orient_f);
		dw = vec3_add(vec3_add(
					vec3_scale(b->orient_r, tl.x * b->inv_inertia.x),
					vec3_scale(b->orient_u, tl.y * b->inv_inertia.y)),
				vec3_scale(b->orient_f, tl.z * b->inv_inertia.z));
	}
	else
	{
		dw.x = torque.x * b->inv_inertia.x;
		dw.y = torque.y * b->inv_inertia.y;
		dw.z = torque.z * b->inv_inertia.z;
	}
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
	double	old_accum;
	double	max_f;

	ia = get_inv_mass(ct->a);
	ib = get_inv_mass(ct->b);
	vt = vec3_sub(rel_v, vec3_scale(ct->normal, vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt) <= 1e-6)
		return ;
	tangent = vec3_norm(vt);
	jt = -vec3_dot(rel_v, tangent) / (ia + ib + ang_term(ct->a, ct->ra,
				tangent, ia) + ang_term(ct->b, ct->rb, tangent, ib));
	old_accum = ct->accum_t;
	max_f = ct->friction * j_normal;
	ct->accum_t = clamp_d(old_accum + jt, -max_f, max_f);
	apply_f_imp(ct, vec3_scale(tangent, ct->accum_t - old_accum), ia, ib);
}

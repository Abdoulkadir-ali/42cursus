/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Applies rotational impulse (torque) to a physics body.
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
 */
void	apply_friction(t_contact *ct, t_vec3 rel_v, double j_normal)
{
	t_vec3	vt;
	t_vec3	tan;
	double	a[4];

	a[0] = get_inv_mass(ct->a);
	a[1] = get_inv_mass(ct->b);
	vt = vec3_sub(rel_v, vec3_scale(ct->normal, vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt) <= 1e-6)
		return ;
	tan = vec3_norm(vt);
	a[2] = -vec3_dot(rel_v, tan) / (a[0] + a[1] + ang_term(ct->a, ct->ra,
				tan, a[0]) + ang_term(ct->b, ct->rb, tan, a[1]));
	a[3] = ct->friction * j_normal;
	a[3] = clamp_d(ct->accum_t + a[2], -a[3], a[3]);
	apply_f_imp(ct, vec3_scale(tan, a[3] - ct->accum_t), a[0], a[1]);
	ct->accum_t = a[3];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torque.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Transfers a contact impulse to the body's angular velocity via torque.
 * Lever arm: r = contact_point - body CoM.
 * Torque:    tau = cross(r, impulse_vec) * inv_inertia.
 * Only effective on compound bodies with meaningful inertia.
 */
void	apply_torque(t_contact *c, t_physics_body *body, double impulse)
{
	t_vec3	r;
	t_vec3	j_vec;
	t_vec3	tau;

	if (!body || body->is_static)
		return ;
	r = vec3_sub(c->contact_point, body->com);
	j_vec = vec3_scale(c->normal, impulse);
	tau = vec3_cross(r, j_vec);
	body->angular_velocity = vec3_add(body->angular_velocity,
			vec3_mul(tau, body->inv_inertia));
}

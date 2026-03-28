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
void	apply_torque(struct s_scene *s, t_contact *c, int body_idx, double impulse)
{
	t_vec3				r;
	t_vec3				j_vec;
	t_vec3				tau;
	t_physics_soa		*soa;
	t_primitive_array	*p;
	int					prim_idx;

	soa = s->physics->soa;
	p = &s->primitives;
	if (body_idx < 0 || soa->is_static[body_idx])
		return ;
	prim_idx = soa->prim_idx[body_idx];
	r = vec3_sub(c->contact_point, vec3(p->px[prim_idx], p->py[prim_idx], p->pz[prim_idx]));
	j_vec = vec3_scale(c->normal, impulse);
	tau = vec3_cross(r, j_vec);
	soa->ang_vx[body_idx] += (float)(tau.x * soa->inv_ix[body_idx]);
	soa->ang_vy[body_idx] += (float)(tau.y * soa->inv_iy[body_idx]);
	soa->ang_vz[body_idx] += (float)(tau.z * soa->inv_iz[body_idx]);
}

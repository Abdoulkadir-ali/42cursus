/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   friction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	apply_f_impulse(t_physics *phys, t_contact *ct, t_vec3 fi,
		double inv_a, double inv_b)
{
	t_physics_soa	*s;
	int				pa;
	int				pb;

	s = phys->soa;
	pa = phys->scene->primitives.phys_idx[ct->idx_a];
	pb = phys->scene->primitives.phys_idx[ct->idx_b];
	if (pa >= 0 && inv_a > 1e-9)
	{
		s->hot.vx[pa] -= (float)(fi.x * inv_a);
		s->hot.vy[pa] -= (float)(fi.y * inv_a);
		s->hot.vz[pa] -= (float)(fi.z * inv_a);
	}
	if (pb >= 0 && inv_b > 1e-9)
	{
		s->hot.vx[pb] += (float)(fi.x * inv_b);
		s->hot.vy[pb] += (float)(fi.y * inv_b);
		s->hot.vz[pb] += (float)(fi.z * inv_b);
	}
}

void	apply_friction(t_physics *phys, t_contact *ct, double inv_a,
		double inv_b, t_vec3 rel_v)
{
	t_vec3	tangent;
	double	denom;
	double	jt;
	int		pa;
	int		pb;

	tangent = vec3_sub(rel_v, vec3_scale(ct->normal,
				vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(tangent) <= 1e-6)
		return ;
	tangent = vec3_norm(tangent);
	pa = phys->scene->primitives.phys_idx[ct->idx_a];
	pb = phys->scene->primitives.phys_idx[ct->idx_b];
	denom = inv_a + inv_b
		+ ang_term(phys, pa, ct->ra, tangent, inv_a)
		+ ang_term(phys, pb, ct->rb, tangent, inv_b);
	if (denom < 1e-9)
		return ;
	jt = -vec3_dot(rel_v, tangent) / denom;
	if (jt < 0.0)
		apply_f_impulse(phys, ct, vec3_scale(tangent, jt * ct->friction),
			inv_a, inv_b);
}

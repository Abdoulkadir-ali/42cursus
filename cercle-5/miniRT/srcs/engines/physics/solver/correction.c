/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:30:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Applies Baumgarte stabilization (pseudo-velocities) to resolve
 * penetration without adding energy to the system.
 */
void	apply_position_correction(t_physics *phys, t_contact *ct,
		double inv_a, double inv_b)
{
	t_primitive_array	*p;
	t_vec3				corr;
	double				depth;
	int					pa;
	int					pb;

	depth = fmax(ct->penetration - 0.01, 0.0);
	if (depth <= 0)
		return ;
	corr = vec3_scale(ct->normal, (depth / (inv_a + inv_b + 1e-9)) * 0.2);
	p = &phys->scene->primitives;
	pa = phys->soa->prim_idx[phys->scene->primitives.phys_idx[ct->idx_a]];
	pb = phys->soa->prim_idx[phys->scene->primitives.phys_idx[ct->idx_b]];
	if (inv_a > 1e-9)
	{
		p->px[pa] -= (float)(corr.x * inv_a);
		p->py[pa] -= (float)(corr.y * inv_a);
		p->pz[pa] -= (float)(corr.z * inv_a);
	}
	if (inv_b > 1e-9)
	{
		p->px[pb] += (float)(corr.x * inv_b);
		p->py[pb] += (float)(corr.y * inv_b);
		p->pz[pb] += (float)(corr.z * inv_b);
	}
}

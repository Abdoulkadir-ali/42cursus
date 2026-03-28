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

/**
 * @brief Applies Baumgarte stabilization (pseudo-velocities) to resolve
 * penetration without adding energy to the system.
 */
void	apply_position_correction(t_contact *ct, double inv_a, double inv_b)
{
	double				depth;
	double				scalar;
	t_primitive_array	*p;
	t_vec3				corr;

	p = &ct->scene->primitives;
	depth = fmax(ct->penetration - 0.01, 0.0);
	if (depth <= 0)
		return ;
	scalar = (depth / (inv_a + inv_b + 1e-9)) * 0.2; /* BAUMGARTE = 0.2 */
	corr = vec3_scale(ct->normal, scalar);
	if (inv_a > 1e-9)
	{
		p->pos[ct->idx_a].x -= corr.x * inv_a;
		p->pos[ct->idx_a].y -= corr.y * inv_a;
		p->pos[ct->idx_a].z -= corr.z * inv_a;
	}
	if (inv_b > 1e-9)
	{
		p->pos[ct->idx_b].x += corr.x * inv_b;
		p->pos[ct->idx_b].y += corr.y * inv_b;
		p->pos[ct->idx_b].z += corr.z * inv_b;
	}
}

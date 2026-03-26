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
	double	depth;
	double	scalar;

	depth = fmax(ct->penetration - SLOP, 0.0);

	scalar = (depth / (inv_a + inv_b + 1e-9)) * BAUMGARTE;
	if (ct->a && inv_a > 1e-9)
		ct->ta->pos = vec3_sub(ct->ta->pos,
				vec3_scale(ct->normal, scalar * inv_a));
	if (ct->b && inv_b > 1e-9)
		ct->tb->pos = vec3_add(ct->tb->pos,
				vec3_scale(ct->normal, scalar * inv_b));
}

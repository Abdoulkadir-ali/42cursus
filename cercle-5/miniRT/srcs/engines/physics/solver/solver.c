/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:51:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static double	get_inv_mass(t_physics_body *body)
{
	if (!body || body->mass <= 1e-6 || body->is_static)
		return (0.0);
	return (1.0 / body->mass);
}

static void	apply_position_correction(t_contact *ct, double inv_a,
		double inv_b)
{
	double	depth;
	double	scalar;
	t_vec3	correction;

	depth = fmax(ct->penetration - SLOP, 0.0);
	scalar = depth / (inv_a + inv_b) * BAUMGARTE;
	correction = vec3_scale(ct->normal, scalar);
	if (ct->a && inv_a > 0.0)
		ct->ta->pos = vec3_sub(ct->ta->pos,
				vec3_scale(correction, inv_a));
	if (ct->b && inv_b > 0.0)
		ct->tb->pos = vec3_add(ct->tb->pos,
				vec3_scale(correction, inv_b));
}

void	solve_positions(t_contact *c, int count)
{
	int		i;
	double	inv_a;
	double	inv_b;

	i = 0;
	while (i < count)
	{
		inv_a = get_inv_mass(c[i].a);
		inv_b = get_inv_mass(c[i].b);
		if (inv_a + inv_b > 1e-8)
			apply_position_correction(&c[i], inv_a, inv_b);
		i++;
	}
}

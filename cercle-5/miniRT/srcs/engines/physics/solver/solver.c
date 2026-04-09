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

double	get_inv_mass(t_physics_body *body)
{
	if (!body || body->mass <= 1e-6 || body->is_static)
		return (0.0);
	return (1.0 / body->mass);
}

static void	apply_position_correction(t_contact *ct, t_physic_engine *en,
		double inv_a, double inv_b)
{
	double	target;
	double	new_lambda;
	double	delta;
	double	scalar;
	t_vec3	da;
	t_vec3	db;

	target = fmax(ct->penetration - en->settings.slop, 0.0);
	new_lambda = fmin(ct->lambda_pos + target * en->settings.baumgarte,
			target);
	delta = new_lambda - ct->lambda_pos;
	ct->lambda_pos = new_lambda;
	if (delta < 1e-9 || inv_a + inv_b < 1e-9)
		return ;
	scalar = delta / (inv_a + inv_b);
	if (ct->a && inv_a > 0.0)
	{
		da = vec3_scale(ct->normal, -scalar * inv_a);
		ct->ta->pos = vec3_add(ct->ta->pos, da);
		ct->a->pos = ct->ta->pos;
		ct->a->center = vec3_add(ct->a->center, da);
	}
	if (ct->b && inv_b > 0.0)
	{
		db = vec3_scale(ct->normal, scalar * inv_b);
		ct->tb->pos = vec3_add(ct->tb->pos, db);
		ct->b->pos = ct->tb->pos;
		ct->b->center = vec3_add(ct->b->center, db);
	}
}

void	solve_positions(t_contact *c, t_physic_engine *engine, size_t count)
{
	size_t	i;
	double	inv_a;
	double	inv_b;

	i = 0;
	while (i < count)
	{
		inv_a = get_inv_mass(c[i].a);
		inv_b = get_inv_mass(c[i].b);
		if (inv_a + inv_b > 1e-8)
			apply_position_correction(&c[i], engine, inv_a, inv_b);
		i++;
	}
}

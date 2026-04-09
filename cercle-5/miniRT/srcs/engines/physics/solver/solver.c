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

static void	update_body_pos(t_physics_body *b, t_transform *t, t_vec3 da)
{
	t->pos = vec3_add(t->pos, da);
	b->pos = t->pos;
	b->center = vec3_add(b->center, da);
}

static void	apply_position_correction(t_contact *ct, t_physic_engine *en,
		double inv_a, double inv_b)
{
	double	new_lambda;
	double	scalar;

	new_lambda = fmin(ct->lambda_pos + fmax(ct->penetration - en->settings.slop,
				0.0) * en->settings.baumgarte, fmax(ct->penetration
				- en->settings.slop, 0.0));
	if (new_lambda - ct->lambda_pos < 1e-9 || inv_a + inv_b < 1e-9)
		return ;
	scalar = (new_lambda - ct->lambda_pos) / (inv_a + inv_b);
	ct->lambda_pos = new_lambda;
	if (ct->a && inv_a > 0.0)
		update_body_pos(ct->a, ct->ta, vec3_scale(ct->normal, -scalar * inv_a));
	if (ct->b && inv_b > 0.0)
		update_body_pos(ct->b, ct->tb, vec3_scale(ct->normal, scalar * inv_b));
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

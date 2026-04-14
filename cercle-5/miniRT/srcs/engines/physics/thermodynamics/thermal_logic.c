/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thermal_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

#define PHYS_DRAG_COEFF    5e-4
#define PHYS_COOL_COEFF    5e-13
#define PHYS_COLL_COEFF    0.05

void	phys_heat_viscous(t_physics_body *b, double dt)
{
	double	w_sq;

	if (!b || b->is_static || b->is_sleeping)
		return ;
	w_sq = vec3_mag_sq(b->angular_velocity);
	b->temperature += PHYS_DRAG_COEFF * w_sq * dt;
}

void	phys_cool_radiative(t_physics_body *b, double dt)
{
	double	t3;

	if (!b || b->is_static || b->temperature < 1.0)
		return ;
	t3 = b->temperature * b->temperature * b->temperature;
	b->temperature /= (1.0 + PHYS_COOL_COEFF * t3 * dt);
	if (b->temperature < 1.0)
		b->temperature = 0.0;
}

void	phys_heat_collision(t_contact *ct, double j, double e)
{
	double	heat;
	double	avg_mass;

	if (j < 0.1)
		return ;
	avg_mass = 1.0;
	if (ct->a && !ct->a->is_static && ct->a->mass > 1e-6)
		avg_mass = ct->a->mass;
	else if (ct->b && !ct->b->is_static && ct->b->mass > 1e-6)
		avg_mass = ct->b->mass;
	heat = (1.0 - e) * j * j * PHYS_COLL_COEFF / avg_mass;
	if (heat < 0.01)
		return ;
	if (ct->a && !ct->a->is_static)
		ct->a->temperature += heat;
	if (ct->b && !ct->b->is_static)
		ct->b->temperature += heat;
}

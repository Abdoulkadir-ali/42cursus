/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	warm_start(t_physic_engine *en)
{
	size_t		i;
	t_contact	*ct;
	double		m[2];

	i = 0;
	while (i < en->contact_count)
	{
		ct = &en->contacts[i++];
		m[0] = get_inv_mass(ct->a);
		m[1] = get_inv_mass(ct->b);
		if ((m[0] < 1e-15 && ct->a && !ct->a->is_static)
			|| (m[1] < 1e-15 && ct->b && !ct->b->is_static))
			continue ;
		if (fabs(ct->accum_n) > 1e-6)
		{
			wake_body(ct->a);
			wake_body(ct->b);
		}
		update_vel(ct, m[0], m[1], ct->accum_n);
	}
}

void	solve_all(t_physic_engine *engine)
{
	size_t	i;

	i = 0;
	while (i < engine->settings.solver_iterations)
	{
		solve_velocities(engine->contacts, engine, engine->contact_count);
		solve_positions(engine->contacts, engine, engine->contact_count);
		i++;
	}
}

void	clamp_all_speeds(t_scene *sc)
{
	size_t	i;

	i = 0;
	while (i < sc->sphere_count)
		clamp_speed(&sc->spheres[i++].phys);
	i = 0;
	while (i < sc->box_count)
		clamp_speed(&sc->boxes[i++].phys);
	i = 0;
	while (i < sc->cylinder_count)
		clamp_speed(&sc->cylinders[i++].phys);
	i = 0;
	while (i < sc->capsule_count)
		clamp_speed(&sc->capsules[i++].phys);
	i = 0;
	while (i < sc->pyramid_count)
		clamp_speed(&sc->pyramids[i++].phys);
	i = 0;
	while (i < sc->rect_count)
		clamp_speed(&sc->rects[i++].phys);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 14:07:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Advance the physics simulation by `delta` seconds, using a fixed
** sub-step accumulator capped at 3 steps to prevent spiral-of-death.
** Flags a scene BVH rebuild when any body moved.
**
** Called exclusively from the render thread — no concurrent readers.
*/
void	physics_step(t_gui *gui, double delta)
{
	double	fixed_dt;
	int		steps;

	if (!gui->scene || !gui->physics_enabled)
		return ;
	fixed_dt = (gui->phys_fixed_dt > 0.0) ? gui->phys_fixed_dt : (1.0 / 60.0);
	if (delta > fixed_dt * 3.0)
		delta = fixed_dt * 3.0;
	gui->phys_accumulator += delta;
	steps = 0;
	while (gui->phys_accumulator >= fixed_dt && steps < 3)
	{
		update_physics(gui->scene, &gui->phys_engine, fixed_dt);
		gui->phys_accumulator -= fixed_dt;
		steps++;
	}
	if (steps > 0)
		gui->render.bvh_needs_rebuild = 1;
}

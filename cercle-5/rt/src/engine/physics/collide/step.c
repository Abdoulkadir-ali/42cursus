/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"
#include "raytracing.h"

void	phys_step(t_app *app, float dt)
{
	int		cells;
	int		i;
	float	step_dt;

	if (!app->phys.enabled || app->phys.paused || app->phys.n == 0)
		return ;
	if (dt > 0.05f)
		dt = 0.05f;
	dt *= app->phys.time_scale;
	phys_pull_positions(&app->phys, app);
	step_dt = dt;
	integrate(app, step_dt);
	cells = build_grid(&app->phys);
	if (cells > 0)
	{
		if (bin_bodies(&app->phys, cells) == 0)
		{
			i = 0;
			while (i < app->phys.n)
			{
				if (app->phys.bodies[i].active)
					collide_neighbors(app, i);
				i++;
			}
		}
		else
		{
			fprintf(stderr, "Physics: skipping neighbor collisions due to bin_bodies failure\n");
		}
	}
	collide_planes_all(app);
	if (push_back_to_scene(app))
	{
		bvh_refit(&app->bvh, app->scene.bvh_objs);
		bvh_prepare_simd(&app->bvh, app->scene.bvh_objs);
		app->dirty = 1;
	}
}

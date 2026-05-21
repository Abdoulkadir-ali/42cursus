/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:22:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	phys_ensure_all_bodies(t_app *app)
{
	size_t		i;
	t_object	*o;
	float		mass;

	if (app->scene.n_bvh > 5000)
		return ;
	i = 0;
	while (i < app->scene.n_bvh)
	{
		o = &app->scene.bvh_objs[i];
		if (o->type != OBJ_PLANE && o->type != OBJ_TRIANGLE
			&& phys_body_for_sphere(&app->phys, (int)i) < 0)
		{
			mass = 1.0f;
			if (o->type == OBJ_BOX)
				mass = 2.0f;
			else if (o->type == OBJ_CYLINDER || o->type == OBJ_CAPSULE)
				mass = 1.5f;
			phys_add_body(&app->phys, (int)i, mass, 0.45f, v3(0, 0, 0));
		}
		i++;
	}
	if (app->phys.n > 0)
		app->phys.enabled = 1;
}

void	phys_rebuild_body_table(t_app *app)
{
	app->phys.n = 0;
	phys_ensure_all_bodies(app);
}

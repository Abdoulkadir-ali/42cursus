/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:22:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	phys_pull_positions(t_phys_world *w, t_app *app)
{
	size_t		i;
	t_object	*o;

	i = 0;
	while (i < (size_t)w->n)
	{
		if (w->bodies[i].sphere_idx >= 0
			&& (size_t)w->bodies[i].sphere_idx < app->scene.n_bvh)
		{
			o = &app->scene.bvh_objs[w->bodies[i].sphere_idx];
			w->bodies[i].pos = object_center(o);
			w->bodies[i].radius_cache = object_bsphere_radius(o);
		}
		i++;
	}
}

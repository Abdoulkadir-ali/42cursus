/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 19:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified DOD motion update for a single primitive.
 */
void	integrate_prim(t_scene *scene, int i, double dt)
{
	t_primitive_array	*p;
	t_transform			t;

	p = &scene->primitives;
	t.pos.x = (double)p->px[i];
	t.pos.y = (double)p->py[i];
	t.pos.z = (double)p->pz[i];
	t.rotation.pitch = (double)p->ax[i];
	t.rotation.yaw = (double)p->ay[i];
	t.rotation.roll = (double)p->az[i];
	phys_dispatch_object(p->physics[i], &t, dt);
	p->px[i] = (float)t.pos.x;
	p->py[i] = (float)t.pos.y;
	p->pz[i] = (float)t.pos.z;
	p->ax[i] = (float)t.rotation.pitch;
	p->ay[i] = (float)t.rotation.yaw;
	p->az[i] = (float)t.rotation.roll;
}

/**
 * @brief Unified DOD integration loop for all scene primitives.
 * Directly updates component arrays in the SoA.
 */
void	integrate_bodies(t_scene *scene, double dt)
{
	t_primitive_array	*p;
	size_t				i;

	if (scene == NULL)
		return ;
	p = &scene->primitives;
	i = 0;
	while (i < p->count)
	{
		if (p->physics[i] != NULL && !p->physics[i]->is_static)
			integrate_prim(scene, (int)i, dt);
		i++;
	}
}

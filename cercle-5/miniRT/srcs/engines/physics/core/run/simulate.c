/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facade.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 03:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <stdlib.h>

/**
 * @brief Minimal physics facade: manages t_physics lifecycle directly inside t_scene.
 * Eliminates legacy global mapping and ensures 100% memory safety.
 */
void	simulate_physics(t_scene *scene, double dt)
{
	t_physics	*phys;

	if (scene == NULL)
		return ;
	phys = (t_physics *)scene->physics;
	if (phys == NULL)
	{
		phys = phys_create(scene);
		if (phys == NULL)
			return ;
		scene->physics = phys;
	}
	if (scene->simulate_physics)
	{
		/* Synchronize simulation state with the unified scene DOD buffers */
		if (phys->needs_bake || phys->baked_version != scene->version)
		{
			phys_bake_scene(phys, scene);
			phys->baked_version = scene->version;
			phys->needs_bake = false;
		}
		update_physics(scene, dt);
	}
}

/**
 * @brief Clean-up entry for the physics engine.
 * To be called by destroy_scene to prevent orphaned physics resources.
 */
void	physics_destroy(t_scene *scene)
{
	if (scene && scene->physics)
	{
		phys_destroy((t_physics *)scene->physics);
		scene->physics = NULL;
	}
}

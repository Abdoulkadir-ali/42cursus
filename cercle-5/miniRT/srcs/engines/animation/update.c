/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 19:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 19:46:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

/**
 * @brief Animates all meshes in the scene that have an assigned skeleton.
 * 
 * This is the high-level entry point for the animation engine.
 * It iterates over all scene meshes and dispatches to the appropriate
 * skinning algorithm (currently GLB is the primary supported format).
 */
void	update_animations(t_scene *scene, double dt)
{
	int		i;
	t_mesh	*mesh;

	if (!scene || scene->clip_count <= 0)
		return ;
	i = 0;
	while (i < scene->mesh_count)
	{
		mesh = &scene->meshes[i];
		if (mesh->skeleton)
			glb_update_mesh_anim(mesh, scene, dt);
		i++;
	}
}

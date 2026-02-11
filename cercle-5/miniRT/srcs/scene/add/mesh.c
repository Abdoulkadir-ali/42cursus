/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Adds a mesh to the scene.
*/
bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	if (!DYNARRAY_ENSURE_INT(&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}

/*
** Adds an animated mesh to the scene.
*/
bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	if (!DYNARRAY_ENSURE_INT(&scene->animated, &scene->anim_count,
			&scene->anim_cap, sizeof(t_skinned_mesh)))
		return (false);
	scene->animated[scene->anim_count++] = animated;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:24:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "raytracing.h"

static void	destroy_scene_arrays(t_scene *scene)
{
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	free(scene->cones);
	free(scene->tris);
	free(scene->rects);
	free(scene->pyramids);
	free(scene->boxes);
	free(scene->capsules);
	free(scene->materials);
	free(scene->lights);
	free(scene->emissive_cache);
}

static void	destroy_scene_animated(t_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->anim_count)
	{
		mesh_free(&scene->animated[i].base);
		free(scene->animated[i].skeleton);
		free(scene->animated[i++].bone_matrices);
	}
	free(scene->animated);
	i = 0;
	while (i < scene->group_count)
	{
		free(scene->groups[i].name);
		free(scene->groups[i++].path);
	}
	free(scene->groups);
}

void	destroy_scene(t_scene *scene)
{
	size_t	i;

	if (!scene)
		return ;
	if (scene->bvh)
		bvh_destroy(scene->bvh);
	free(scene->name);
	destroy_scene_arrays(scene);
	i = 0;
	while (i < scene->mesh_count)
		mesh_free(&scene->meshes[i++]);
	free(scene->meshes);
	destroy_scene_animated(scene);
	if (scene->pool)
	{
		threads_destroy(scene->pool);
		free(scene->pool);
	}
	pthread_rwlock_destroy(&scene->bvh_lock);
	free(scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 10:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "raytracing.h"

/**
 * @brief Frees the assets (meshes and animated meshes) in the scene.
 * @param sc Pointer to the scene.
 */
static void	destroy_assets(t_scene *sc)
{
	int	i;

	i = 0;
	while (i < sc->mesh_count)
		mesh_free(&sc->meshes[i++]);
	free(sc->meshes);
	i = 0;
	while (i < sc->anim_count)
	{
		mesh_free(&sc->animated[i].base);
		free(sc->animated[i].skeleton);
		free(sc->animated[i].bone_matrices);
		i++;
	}
	free(sc->animated);
}

/**
 * @brief Frees the geometry arrays and metadata in the scene.
 * @param sc Pointer to the scene.
 */
static void	destroy_geometry(t_scene *sc)
{
	int	i;

	free(sc->spheres);
	free(sc->planes);
	free(sc->cylinders);
	free(sc->cones);
	free(sc->tris);
	free(sc->rects);
	free(sc->pyramids);
	free(sc->boxes);
	free(sc->capsules);
	i = 0;
	while (i < sc->group_count)
	{
		free(sc->groups[i].name);
		free(sc->groups[i].path);
		i++;
	}
	free(sc->groups);
}

/**
 * @brief Frees all memory associated with the scene and its objects.
 * @param scene Pointer to the scene to be destroyed.
 */
void	destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->bvh)
		bvh_destroy(scene->bvh);
	free(scene->name);
	destroy_assets(scene);
	destroy_geometry(scene);
	free(scene->materials);
	free(scene->lights);
	free(scene->emissive_cache);
	free(scene);
}

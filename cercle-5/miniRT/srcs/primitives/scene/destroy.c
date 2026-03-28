/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:22:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "physics.h"

/**
 * @brief Frees the assets (meshes and animated meshes) in the scene.
 * @param sc Pointer to the scene.
 */
static void	destroy_assets(t_scene *sc)
{
	/* Animated skinned-meshes may hold internal allocations; most callers
	 * manage those via the loader code. To avoid referencing an incomplete
	 * skinned-mesh type here we only free the animated array container.
	 * Individual mesh backing data is freed elsewhere when applicable.
	 */
	if (sc->animated)
		free(sc->animated);
}

/**
 * @brief Frees the geometry arrays and metadata in the scene.
 * @param sc Pointer to the scene.
 */
static void	destroy_geometry(t_scene *sc)
{
	int k;

	/* Free primitive SoA arrays */
	if (sc->primitives.types)
		free(sc->primitives.types);
	if (sc->primitives.px)
		free(sc->primitives.px);
	if (sc->primitives.py)
		free(sc->primitives.py);
	if (sc->primitives.pz)
		free(sc->primitives.pz);
	if (sc->primitives.ax)
		free(sc->primitives.ax);
	if (sc->primitives.ay)
		free(sc->primitives.ay);
	if (sc->primitives.az)
		free(sc->primitives.az);
	if (sc->primitives.tx)
		free(sc->primitives.tx);
	if (sc->primitives.ty)
		free(sc->primitives.ty);
	if (sc->primitives.tz)
		free(sc->primitives.tz);
	if (sc->primitives.radii)
		free(sc->primitives.radii);
	if (sc->primitives.heights)
		free(sc->primitives.heights);
	if (sc->primitives.ex)
		free(sc->primitives.ex);
	if (sc->primitives.ey)
		free(sc->primitives.ey);
	if (sc->primitives.ez)
		free(sc->primitives.ez);
	if (sc->primitives.mat_ids)
		free(sc->primitives.mat_ids);






	/* Free triangle SoA arrays */
	for (k = 0; k < 3; ++k)
	{
		if (sc->tri_soa.vx[k])
			free(sc->tri_soa.vx[k]);
		if (sc->tri_soa.vy[k])
			free(sc->tri_soa.vy[k]);
		if (sc->tri_soa.vz[k])
			free(sc->tri_soa.vz[k]);
	}
	for (k = 0; k < 2; ++k)
	{
		if (sc->tri_soa.ex[k])
			free(sc->tri_soa.ex[k]);
		if (sc->tri_soa.ey[k])
			free(sc->tri_soa.ey[k]);
		if (sc->tri_soa.ez[k])
			free(sc->tri_soa.ez[k]);
	}
	if (sc->tri_soa.nx)
		free(sc->tri_soa.nx);
	if (sc->tri_soa.ny)
		free(sc->tri_soa.ny);
	if (sc->tri_soa.nz)
		free(sc->tri_soa.nz);
	if (sc->tri_soa.tx)
		free(sc->tri_soa.tx);
	if (sc->tri_soa.ty)
		free(sc->tri_soa.ty);
	if (sc->tri_soa.tz)
		free(sc->tri_soa.tz);
	if (sc->tri_soa.mat_ids)
		free(sc->tri_soa.mat_ids);
}

/**
 * @brief Frees all memory associated with the scene and its objects.
 * @param scene Pointer to the scene to be destroyed.
 */
void	destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->name);
	destroy_assets(scene);
	destroy_geometry(scene);

	free(scene->materials);
	free(scene->lights);
	free(scene->emissive_cache);
	free(scene);
}

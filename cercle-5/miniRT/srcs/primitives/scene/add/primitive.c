/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Performs synchronized parallel reallocation for the orientation-aware SoA.
 */
static bool	realloc_prim_soa(t_primitive_array *arr, size_t new_cap)
{
	uint8_t		*nty;
	float		*nx, *ny, *nz;
	float		*nax, *nay, *naz;
	float		*ntx, *nty_t, *ntz;
	float		*nex, *ney, *nez;
	float		*nr, *nh;
	uint16_t	*nm;

	nty = realloc(arr->types, new_cap * 1);
	nx = realloc(arr->px, new_cap * 4);
	ny = realloc(arr->py, new_cap * 4);
	nz = realloc(arr->pz, new_cap * 4);
	nax = realloc(arr->ax, new_cap * 4);
	nay = realloc(arr->ay, new_cap * 4);
	naz = realloc(arr->az, new_cap * 4);
	ntx = realloc(arr->tx, new_cap * 4);
	nty_t = realloc(arr->ty, new_cap * 4);
	ntz = realloc(arr->tz, new_cap * 4);
	nex = realloc(arr->ex, new_cap * 4);
	ney = realloc(arr->ey, new_cap * 4);
	nez = realloc(arr->ez, new_cap * 4);
	nr = realloc(arr->radii, new_cap * 4);
	nh = realloc(arr->heights, new_cap * 4);
	nm = realloc(arr->mat_ids, new_cap * 2);
	if (!nty || !nx || !ny || !nz || !nax || !nay || !naz || !ntx || !nty_t || !ntz || !nex || !ney || !nez || !nr || !nh || !nm)
		return (false);
	arr->types = nty; arr->px = nx; arr->py = ny; arr->pz = nz;
	arr->ax = nax; arr->ay = nay; arr->az = naz;
	arr->tx = ntx; arr->ty = nty_t; arr->tz = ntz;
	arr->ex = nex; arr->ey = ney; arr->ez = nez;
	arr->radii = nr; arr->heights = nh; arr->mat_ids = nm;
	arr->capacity = new_cap;
	return (true);
}

/**
 * @brief Ensures sufficient space for new primitives.
 */
static bool	ensure_prim_cap(t_primitive_array *arr)
{
	size_t	n;

	if (arr->count < arr->capacity)
		return (true);
	n = (arr->capacity == 0) ? 1024 : arr->capacity * 2;
	return (realloc_prim_soa(arr, n));
}

/**
 * @brief Unified DOD injection including orientation basis (Normal + Tangent).
 */
bool	scene_add_primitive(t_scene *scene, t_prim_params params, t_prim_type type)
{
	size_t	idx;

	if (!ensure_prim_cap(&scene->primitives))
		return (false);
	idx = scene->primitives.count++;
	scene->primitives.types[idx] = (uint8_t)type;
	scene->primitives.px[idx] = (float)params.pos.x;
	scene->primitives.py[idx] = (float)params.pos.y;
	scene->primitives.pz[idx] = (float)params.pos.z;
	scene->primitives.ax[idx] = (float)params.axis.x;
	scene->primitives.ay[idx] = (float)params.axis.y;
	scene->primitives.az[idx] = (float)params.axis.z;
	scene->primitives.tx[idx] = (float)params.tangent.x;
	scene->primitives.ty[idx] = (float)params.tangent.y;
	scene->primitives.tz[idx] = (float)params.tangent.z;
	scene->primitives.ex[idx] = (float)params.extents.x;
	scene->primitives.ey[idx] = (float)params.extents.y;
	scene->primitives.ez[idx] = (float)params.extents.z;
	scene->primitives.radii[idx] = params.radius;
	scene->primitives.heights[idx] = params.height;
	scene->primitives.mat_ids[idx] = (uint16_t)params.mat_id;
	scene->primitives.physics[idx] = NULL;
	return (true);
}

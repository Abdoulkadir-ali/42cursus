/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 05:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 19:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Performs synchronized parallel reallocation for the triangle SoA.
 */
static bool	realloc_tri_soa(t_tri_array *arr, size_t new_cap)
{
	float		*nv[9];
	float		*nn[3];
	uint16_t	*nmats;

	nv[0] = realloc(arr->vx0, new_cap * 4);
	nv[1] = realloc(arr->vy0, new_cap * 4);
	nv[2] = realloc(arr->vz0, new_cap * 4);
	nv[3] = realloc(arr->vx1, new_cap * 4);
	nv[4] = realloc(arr->vy1, new_cap * 4);
	nv[5] = realloc(arr->vz1, new_cap * 4);
	nv[6] = realloc(arr->vx2, new_cap * 4);
	nv[7] = realloc(arr->vy2, new_cap * 4);
	nv[8] = realloc(arr->vz2, new_cap * 4);
	nn[0] = realloc(arr->nx, new_cap * 4);
	nn[1] = realloc(arr->ny, new_cap * 4);
	nn[2] = realloc(arr->nz, new_cap * 4);
	nmats = realloc(arr->mat_ids, new_cap * 2);
	if (!nv[0] || !nv[1] || !nv[2] || !nv[3] || !nv[4] || !nv[5] || !nv[6] || !nv[7] || !nv[8] || !nn[0] || !nn[1] || !nn[2] || !nmats)
		return (false);
	arr->vx0 = nv[0]; arr->vy0 = nv[1]; arr->vz0 = nv[2];
	arr->vx1 = nv[3]; arr->vy1 = nv[4]; arr->vz1 = nv[5];
	arr->vx2 = nv[6]; arr->vy2 = nv[7]; arr->vz2 = nv[8];
	arr->nx = nn[0]; arr->ny = nn[1]; arr->nz = nn[2];
	arr->mat_ids = nmats;
	arr->cap = new_cap;
	return (true);
}

/**
 * @brief Ensures sufficient space for triangles in the scene pool.
 */
static bool	ensure_tri_cap(t_tri_array *arr)
{
	size_t	n;

	if (arr->count < arr->cap)
		return (true);
	n = (arr->cap == 0) ? 1024 : arr->cap * 2;
	return (realloc_tri_soa(arr, n));
}

/**
 * @brief DOD-aligned triangle injection into the scene pool.
 */
bool	scene_add_tri(t_scene *scene, t_vec3 v[3], int mat_id)
{
	size_t	i;
	t_vec3	n;

	if (!ensure_tri_cap(&scene->tri_soa))
		return (false);
	i = scene->tri_soa.count++;
	scene->tri_soa.vx0[i] = (float)v[0].x;
	scene->tri_soa.vy0[i] = (float)v[0].y;
	scene->tri_soa.vz0[i] = (float)v[0].z;
	scene->tri_soa.vx1[i] = (float)v[1].x;
	scene->tri_soa.vy1[i] = (float)v[1].y;
	scene->tri_soa.vz1[i] = (float)v[1].z;
	scene->tri_soa.vx2[i] = (float)v[2].x;
	scene->tri_soa.vy2[i] = (float)v[2].y;
	scene->tri_soa.vz2[i] = (float)v[2].z;
	n = vec3_norm(vec3_cross(vec3_sub(v[1], v[0]), vec3_sub(v[2], v[0])));
	scene->tri_soa.nx[i] = (float)n.x;
	scene->tri_soa.ny[i] = (float)n.y;
	scene->tri_soa.nz[i] = (float)n.z;
	scene->tri_soa.mat_ids[i] = (uint16_t)mat_id;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 03:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD Implementation: Gathers bounds from the primitive SoA.
 */
static size_t	collect_primitives_soa(t_scene *sc, t_build_item *items)
{
	t_primitive_array	*p;
	size_t				i;

	p = &sc->primitives;
	i = 0;
	while (i < p->count)
	{
		items[i].ref = (t_bvh_ref){p->types[i], (int)i};
		items[i].aabb = get_primitive_aabb_soa(p, (int)i);
		items[i].centroid = vec3(p->px[i], p->py[i], p->pz[i]);
		i++;
	}
	return (i);
}

/**
 * @brief DOD Implementation: Gathers bounds from the triangle SoA.
 */
static size_t	collect_triangles_soa(t_scene *sc, t_build_item *items, size_t n)
{
	t_tri_array	*t;
	size_t		i;

	t = &sc->tri_soa;
	i = 0;
	while (i < t->count)
	{
		items[n + i].ref = (t_bvh_ref){TYPE_TRI, (int)i};
		items[n + i].aabb = get_tri_aabb_soa(t, (int)i);
		/* Simple centroid: Average of vertices */
		items[n + i].centroid = vec3(
			(t->vx[0][i] + t->vx[1][i] + t->vx[2][i]) / 3.0,
			(t->vy[0][i] + t->vy[1][i] + t->vy[2][i]) / 3.0,
			(t->vz[0][i] + t->vz[1][i] + t->vz[2][i]) / 3.0);
		i++;
	}
	return (n + i);
}

/**
 * @brief High-performance DOD object collection for BVH construction.
 * Iterates through unified SoA arrays instead of fragmented legacy AoS.
 */
size_t	collect_objects(t_scene *scene, t_build_item *items)
{
	size_t	n;

	if (scene == NULL || items == NULL)
		return (0);
	n = collect_primitives_soa(scene, items);
	n = collect_triangles_soa(scene, items, n);
	return (n);
}

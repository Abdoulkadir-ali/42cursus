/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	is_emissive(const t_scene *sc, int mat_id)
{
	t_vec3	e;

	if (mat_id < 0 || mat_id >= sc->mat_count)
		return (false);
	e = sc->materials[mat_id].emission;
	return ((e.x * e.x + e.y * e.y + e.z * e.z) > 1.0);
}

static int	add_emissives_1(const t_scene *sc, t_emissive_ref *ca, int n)
{
	int	i;

	i = -1;
	while (++i < sc->sphere_count)
		if (is_emissive(sc, sc->spheres[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_SPHERE, i};
	i = -1;
	while (++i < sc->tri_count)
		if (is_emissive(sc, sc->tris[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_TRI, i};
	i = -1;
	while (++i < sc->rect_count)
		if (is_emissive(sc, sc->rects[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_RECT, i};
	return (n);
}

static int	add_emissives_2(const t_scene *sc, t_emissive_ref *ca, int n)
{
	int	i;

	i = -1;
	while (++i < sc->pyramid_count)
		if (is_emissive(sc, sc->pyramids[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_PYRAMID, i};
	i = -1;
	while (++i < sc->box_count)
		if (is_emissive(sc, sc->boxes[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_BOX, i};
	i = -1;
	while (++i < sc->capsule_count)
		if (is_emissive(sc, sc->capsules[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_CAPSULE, i};
	i = -1;
	while (++i < sc->mesh_count)
		if (is_emissive(sc, sc->meshes[i].mat_id))
			ca[n++] = (t_emissive_ref){TYPE_MESH, i};
	return (n);
}

/**
 * @brief Identifies all emissive shapes in the scene and builds a cache for 
 * fast light sampling during rendering.
 */
void	build_emissive_cache(t_scene *sc)
{
	t_emissive_ref	*cache;
	int				cap;
	int				n;

	free(sc->emissive_cache);
	sc->emissive_cache = NULL;
	sc->emissive_n = 0;
	cap = sc->sphere_count + sc->tri_count + sc->rect_count
		+ sc->pyramid_count + sc->box_count + sc->capsule_count
		+ sc->mesh_count;
	if (cap == 0)
		return ;
	cache = malloc(sizeof(t_emissive_ref) * cap);
	if (!cache)
		return ;
	n = add_emissives_1(sc, cache, 0);
	sc->emissive_cache = cache;
	sc->emissive_n = add_emissives_2(sc, cache, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em_cache.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:46:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:46:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	cache_primary_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	i = 0;
	while (i < sc->sphere_count)
	{
		if (is_emissive(sc, sc->spheres[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_SPHERE, i);
		i++;
	}
}

static void	cache_secondary_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	i = 0;
	while (i < sc->tri_count)
	{
		if (is_emissive(sc, sc->tris[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_TRI, i);
		i++;
	}
	i = 0;
	while (i < sc->rect_count)
	{
		if (is_emissive(sc, sc->rects[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_RECT, i);
		i++;
	}
}

static void	cache_complex_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	i = 0;
	while (i < sc->mesh_count)
	{
		if (is_emissive(sc, sc->meshes[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_MESH, i);
		i++;
	}
}

void	build_emissive_cache(t_scene *sc)
{
	t_emissive_ref	*cache;
	size_t			cap;
	size_t			n;

	cap = sc->sphere_count + sc->tri_count + sc->rect_count + sc->pyramid_count;
	cap += sc->box_count + sc->capsule_count + sc->mesh_count;
	if (cap == 0)
		return ;
	cache = ft_calloc(cap, sizeof(t_emissive_ref));
	if (!cache)
		return ;
	n = 0;
	cache_primary_em(sc, cache, &n);
	cache_secondary_em(sc, cache, &n);
	cache_complex_em(sc, cache, &n);
	sc->emissive_cache = cache;
	sc->emissive_n = n;
}

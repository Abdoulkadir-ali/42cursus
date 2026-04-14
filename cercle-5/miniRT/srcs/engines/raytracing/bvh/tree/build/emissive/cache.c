/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:46:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:55:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	set_em_reach(t_scene *sc, size_t i, t_emissive_ref *ref)
{
	t_material	*m;
	double		r;
	double		reach;

	m = &sc->materials[sc->spheres[i].mat_id];
	r = fmax(fabs(sc->spheres[i].transform.scale.x), 1.0)
		* sqrt(sc->spheres[i].radius_sq);
	reach = fmax(r * 3.0, 3.0) * fmax(1.0, m->em_radius);
	reach = reach * sqrt(fmin(fmax(1.0, m->em_intensity),
				50000.0 * 50000.0)) + r;
	ref->reach_center_sq = reach * reach;
}

static void	cache_primary_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t			i;
	t_emissive_ref	ref;

	i = 0;
	while (i < sc->sphere_count)
	{
		if (sc->spheres[i].radius_sq > 0.0
			&& is_emissive(sc, sc->spheres[i].mat_id))
		{
			ref = init_emissive_ref(TYPE_SPHERE, i);
			set_em_reach(sc, i, &ref);
			cache[(*n)++] = ref;
		}
		i++;
	}
}

static void	cache_other_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	cache_secondary_em(sc, cache, n);
	cache_volume_em(sc, cache, n);
	i = -1;
	while (++i < sc->plane_count)
		if (is_emissive(sc, sc->planes[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_PLANE, i);
	i = -1;
	while (++i < sc->mesh_count)
		if (is_emissive(sc, sc->meshes[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_MESH, i);
}

void	build_emissive_cache(t_scene *sc)
{
	t_emissive_ref	*cache;
	size_t			cap;
	size_t			n;
	size_t			i;

	i = -1;
	while (++i < sc->mat_count)
		if (sc->materials[i].temperature > 0.0)
			apply_blackbody_to_mat(&sc->materials[i]);
	cap = sc->sphere_count + sc->tri_count + sc->rect_count + sc->pyramid_count;
	cap += sc->box_count + sc->capsule_count + sc->mesh_count + sc->plane_count;
	cap += sc->cylinder_count + sc->cone_count;
	if (cap == 0)
		return ;
	cache = ft_calloc(cap, sizeof(t_emissive_ref));
	if (!cache)
		return ;
	n = 0;
	cache_primary_em(sc, cache, &n);
	cache_other_em(sc, cache, &n);
	sc->emissive_cache = cache;
	sc->emissive_n = n;
}

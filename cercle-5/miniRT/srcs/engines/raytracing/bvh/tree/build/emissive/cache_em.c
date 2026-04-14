/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache_em.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:46:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:55:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	cache_secondary_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	i = -1;
	while (++i < sc->tri_count)
		if (is_emissive(sc, sc->tris[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_TRI, i);
	i = -1;
	while (++i < sc->rect_count)
		if (is_emissive(sc, sc->rects[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_RECT, i);
}

void	cache_volume_em(t_scene *sc, t_emissive_ref *cache, size_t *n)
{
	size_t	i;

	i = -1;
	while (++i < sc->box_count)
		if (is_emissive(sc, sc->boxes[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_BOX, i);
	i = -1;
	while (++i < sc->capsule_count)
		if (is_emissive(sc, sc->capsules[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_CAPSULE, i);
	i = -1;
	while (++i < sc->cylinder_count)
		if (is_emissive(sc, sc->cylinders[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_CYLINDER, i);
	i = -1;
	while (++i < sc->cone_count)
		if (is_emissive(sc, sc->cones[i].mat_id))
			cache[(*n)++] = init_emissive_ref(TYPE_CONE, i);
}

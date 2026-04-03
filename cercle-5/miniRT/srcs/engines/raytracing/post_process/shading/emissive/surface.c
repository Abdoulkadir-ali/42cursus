/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	em_py(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_pyramid	*py;

	py = &sc->pyramids[ref.index];
	sha->aux_v = vec3_sub(py->transform.pos, sha->hit->point);
	apply_em(sha, total, &sc->materials[py->mat_id], py->base_size * 0.5);
}

void	em_surf(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_tri_shape	*tr;

	if (ref.type == TYPE_TRI)
	{
		tr = &sc->tris[ref.index];
		sha->aux_v = vec3_sub(vec3_scale(vec3_add(vec3_add(tr->v[0], tr->v[1]),
						tr->v[2]), 1.0 / 3.0), sha->hit->point);
		apply_em(sha, total, &sc->materials[tr->mat_id], 0.5);
	}
	else if (ref.type == TYPE_RECT)
	{
		sha->aux_v = vec3_sub(sc->rects[ref.index].transform.pos,
				sha->hit->point);
		apply_em(sha, total, &sc->materials[sc->rects[ref.index].mat_id], 0.7);
	}
	else if (ref.type == TYPE_PYRAMID)
		em_py(sha, sc, total, ref);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	em_tri(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_tri_shape	*tr;
	t_vec3		closest;

	tr = &sc->tris[ref.index];
	closest = closest_pt_tri(sha->hit->point, tr->v[0], tr->v[1], tr->v[2]);
	sha->aux_v = vec3_sub(closest, sha->hit->point);
	sha->em_normal = tr->normal;
	apply_em(sha, total, &sc->materials[tr->mat_id], 0.5);
}

void	em_rect(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_rect	*rc;
	t_vec3	cl;
	double	e0;
	double	e1;

	rc = &sc->rects[ref.index];
	cl = closest_pt_rect(sha->hit->point, rc->v[0], rc->v[1], rc->v[3]);
	e0 = vec3_mag(vec3_sub(rc->v[1], rc->v[0]));
	e1 = vec3_mag(vec3_sub(rc->v[3], rc->v[0]));
	sha->aux_v = vec3_sub(cl, sha->hit->point);
	sha->em_normal = rc->normal;
	apply_em(sha, total, &sc->materials[rc->mat_id], fmax(e0, e1) * 0.5);
}

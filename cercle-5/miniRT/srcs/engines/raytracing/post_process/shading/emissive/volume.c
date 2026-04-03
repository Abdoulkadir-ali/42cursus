/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	em_cap(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_capsule	*cp;

	cp = &sc->capsules[ref.index];
	sha->aux_v = vec3_sub(cp->transform.pos, sha->hit->point);
	apply_em(sha, total, &sc->materials[cp->mat_id],
		cp->radius + cp->half_height);
}

void	em_vol(t_shading *sha, t_scene *sc, t_vec3 *total,
				t_emissive_ref ref)
{
	t_sphere	*sp;
	t_box		*bx;

	if (ref.type == TYPE_SPHERE)
	{
		sp = &sc->spheres[ref.index];
		sha->aux_v = vec3_sub(sp->transform.pos, sha->hit->point);
		apply_em(sha, total, &sc->materials[sp->mat_id],
			fmax(fabs(sp->transform.scale.x), 1.0) * sqrt(sp->radius_sq));
	}
	else if (ref.type == TYPE_BOX)
	{
		bx = &sc->boxes[ref.index];
		sha->aux_v = vec3_sub(bx->transform.pos, sha->hit->point);
		apply_em(sha, total, &sc->materials[bx->mat_id],
			fmax(fmax(bx->half_extents.x, bx->half_extents.y),
				bx->half_extents.z));
	}
	else if (ref.type == TYPE_CAPSULE)
		em_cap(sha, sc, total, ref);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	emissive_box(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	double	rad;

	rad = fmax(fmax(sc->boxes[r.index].half_extents.x,
				sc->boxes[r.index].half_extents.y),
			sc->boxes[r.index].half_extents.z);
	ctx->aux_v = vec3_sub(sc->boxes[r.index].transform.pos,
			ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->boxes[r.index].mat_id],
		vec3(rad, 0, 0));
}

static void	emissive_capsule(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	ctx->aux_v = vec3_sub(sc->capsules[r.index].transform.pos,
			ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->capsules[r.index].mat_id],
		vec3(sc->capsules[r.index].radius
			+ sc->capsules[r.index].half_height, 0, 0));
}

static void	emissive_mesh(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	t_vec3	c;

	c = vec3_add(sc->meshes[r.index].transform.pos, vec3_scale(vec3_add(
					sc->meshes[r.index].bbox.min,
					sc->meshes[r.index].bbox.max), HALF_SCALE));
	ctx->aux_v = vec3_sub(c, ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->meshes[r.index].mat_id],
		vec3(vec3_mag(vec3_scale(vec3_sub(sc->meshes[r.index].bbox.max,
						sc->meshes[r.index].bbox.min), HALF_SCALE)), 0, 0));
}

void	emissive_complex(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	if (r.type == TYPE_BOX)
		emissive_box(ctx, sc, tot, r);
	else if (r.type == TYPE_CAPSULE)
		emissive_capsule(ctx, sc, tot, r);
	else if (r.type == TYPE_MESH)
		emissive_mesh(ctx, sc, tot, r);
}

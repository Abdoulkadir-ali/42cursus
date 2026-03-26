/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	emissive_sphere(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	double	rad;

	rad = fmax(fabs(sc->spheres[r.index].transform.scale.x), 1.0)
		* sqrt(sc->spheres[r.index].radius_sq);
	ctx->aux_v = vec3_sub(sc->spheres[r.index].transform.pos,
			ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->spheres[r.index].mat_id],
		vec3(rad, 0, 0));
}

static void	emissive_tri(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	t_vec3	c;

	c = vec3_scale(vec3_add(vec3_add(sc->tris[r.index].v[0],
					sc->tris[r.index].v[1]), sc->tris[r.index].v[2]),
			1.0 / 3.0);
	ctx->aux_v = vec3_sub(c, ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->tris[r.index].mat_id],
		vec3(HALF_SCALE, 0, 0));
}

static void	emissive_rect(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	ctx->aux_v = vec3_sub(sc->rects[r.index].transform.pos,
			ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->rects[r.index].mat_id],
		vec3(0.7, 0, 0));
}

static void	emissive_pyramid(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	ctx->aux_v = vec3_sub(sc->pyramids[r.index].transform.pos,
			ctx->hit->point);
	apply_emissive_hit(ctx, tot, &sc->materials[sc->pyramids[r.index].mat_id],
		vec3(sc->pyramids[r.index].base_size * HALF_SCALE, 0, 0));
}

void	emissive_primary(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r)
{
	if (r.type == TYPE_SPHERE)
		emissive_sphere(ctx, sc, tot, r);
	else if (r.type == TYPE_TRI)
		emissive_tri(ctx, sc, tot, r);
	else if (r.type == TYPE_RECT)
		emissive_rect(ctx, sc, tot, r);
	else if (r.type == TYPE_PYRAMID)
		emissive_pyramid(ctx, sc, tot, r);
}

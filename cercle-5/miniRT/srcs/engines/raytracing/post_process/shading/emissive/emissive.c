/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	finalize_em_val(t_shading *sha, t_vec3 *total,
				t_material *mat, t_shading_ctx *ctx)
{
	double	bright;
	double	att;

	if (is_in_shadow(sha->bvh, vec3_add(sha->hit->point,
				vec3_scale(sha->hit->normal, EPSILON * 10.0)), ctx->ldir,
			ctx->d_surf))
		return ;
	bright = vec3_mag(mat->emission) / 255.0 * mat->em_intensity;
	att = 1.0 / (1.0 + ctx->d_surf * ctx->d_surf);
	*total = vec3_add(*total, pixel_color(sha->albedo, mat->emission,
				bright * ctx->ndotl * att * ctx->emitter_facing));
	sha->aux_v = vec3_scale(ctx->ldir,
			bright * sha->mat.specular * att * ctx->emitter_facing);
}

static void	apply_em_val(t_shading *sha, t_vec3 *total,
				t_material *mat, double r)
{
	t_shading_ctx	ctx;
	t_vec3			tl;

	tl = sha->aux_v;
	sha->aux_v = vec3(0, 0, 0);
	if (vec3_mag_sq(tl) > fmax(r * 6.0, 8.0) * fmax(r * 6.0, 8.0))
		return ;
	ctx.d_surf = vec3_mag(tl) - r - 0.01;
	if (ctx.d_surf <= 0.0)
		return ;
	ctx.ldir = vec3_norm(tl);
	ctx.emitter_facing = 1.0;
	if (vec3_mag_sq(sha->em_normal) > 1e-6)
	{
		ctx.emitter_facing = vec3_dot(sha->em_normal,
				vec3_scale(ctx.ldir, -1.0));
		if (ctx.emitter_facing <= 0.0)
			return ;
	}
	ctx.ndotl = vec3_dot(sha->hit->normal, ctx.ldir);
	if (ctx.ndotl < 0.02)
		return ;
	finalize_em_val(sha, total, mat, &ctx);
}

void	apply_em(t_shading *sha, t_vec3 *total, t_material *mat, double r)
{
	double	spec;
	t_vec3	ldir;
	double	spec_val;

	ldir = vec3_norm(sha->aux_v);
	apply_em_val(sha, total, mat, r);
	spec_val = vec3_mag(sha->aux_v);
	spec = (double) powf((float) fmax(0.0, vec3_dot(sha->hit->normal,
					vec3_norm(vec3_add(ldir,
							vec3_scale(sha->ray->direction, -1.0))))),
			(float) sha->mat.shininess);
	*total = vec3_add(*total, vec3_scale(mat->emission,
				spec_val * spec));
}

void	add_emissive_lighting(t_shading *sha, t_scene *sc, t_vec3 *total)
{
	size_t			i;
	t_emissive_ref	ref;
	t_mesh			*m;

	i = 0;
	while (i < sc->emissive_n)
	{
		ref = sc->emissive_cache[i++];
		em_vol(sha, sc, total, ref);
		em_surf(sha, sc, total, ref);
		if (ref.type == TYPE_MESH)
		{
			m = &sc->meshes[ref.index];
			sha->aux_v = vec3_sub(vec3_add(m->transform.pos, vec3_scale(
							vec3_add(m->bbox.min, m->bbox.max), 0.5)),
					sha->hit->point);
			sha->em_normal = vec3(0, 0, 0);
			apply_em(sha, total, &sc->materials[m->mat_id], vec3_mag(
					vec3_scale(vec3_sub(m->bbox.max, m->bbox.min), 0.5)));
		}
	}
}

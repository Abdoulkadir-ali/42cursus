/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:37:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 22:03:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	em_reach_check(t_shading *sha, t_material *mat,
			double r, t_shading_ctx *ctx)
{
	double	tl_sq;
	double	reach;

	tl_sq = vec3_mag_sq(sha->aux_v);
	reach = fmax(r * 3.0, 3.0) * fmax(1.0, mat->em_radius);
	reach = reach * reach * fmin(fmax(1.0, mat->em_intensity), 2.5e9);
	if (tl_sq > reach)
		return (false);
	ctx->d_surf = fmax(sqrt(tl_sq) - r * 0.05, 1e-3);
	return (true);
}

static double	em_val_check(t_shading *sha, t_material *mat,
			t_shading_ctx *ctx, double r)
{
	t_vec3		org;
	double		bright;
	double		att;

	if (vec3_mag_sq(sha->em_normal) > 1e-6)
		ctx->emitter_facing = fmax(0.0, vec3_dot(sha->em_normal,
					vec3_scale(ctx->ldir, -1.0)));
	if (ctx->emitter_facing <= 0.0 && vec3_mag_sq(sha->em_normal) > 1e-6)
		return (0.0);
	ctx->ndotl = vec3_dot(sha->hit->normal, ctx->ldir);
	if (ctx->ndotl < 0.02)
		return (0.0);
	org = vec3_add(sha->hit->point,
			vec3_scale(sha->hit->normal, EPSILON * 10.0));
	if (is_in_shadow(sha->bvh, org, ctx->ldir, ctx->d_surf - EPSILON))
		return (0.0);
	bright = fmin(vec3_mag(mat->emission) / 255.0
			* mat->em_intensity / fmax(4.0 * PI * r * r, 1.0), 50000.0);
	att = 1.0 / (1.0 + ctx->d_surf * ctx->d_surf * 0.1);
	return (bright * ctx->ndotl * att * ctx->emitter_facing);
}

static void	apply_em_val(t_shading *sha, t_vec3 *total,
			t_material *mat, double r)
{
	t_shading_ctx	ctx;
	double			val;

	if (em_reach_check(sha, mat, r, &ctx) == false)
		return ;
	ctx.ldir = vec3_norm(sha->aux_v);
	sha->aux_v = vec3(0, 0, 0);
	ctx.emitter_facing = 1.0;
	val = em_val_check(sha, mat, &ctx, r);
	if (val < 1e-10)
		return ;
	*total = vec3_add(*total, pixel_color(sha->albedo, mat->emission, val));
	sha->aux_v = vec3_scale(ctx.ldir, val * sha->mat.specular);
}

void	apply_em(t_shading *sha, t_vec3 *total, t_material *mat, double r)
{
	double	spec;
	t_vec3	ldir;
	double	spec_val;
	float	ndoth;
	t_vec3	half;

	ldir = vec3_norm(sha->aux_v);
	apply_em_val(sha, total, mat, r);
	spec_val = vec3_mag(sha->aux_v);
	if (spec_val < 1e-6)
		return ;
	spec_val = fmin(spec_val, 2.0);
	half = vec3_norm(vec3_add(ldir,
				vec3_scale(sha->ray->direction, -1.0)));
	ndoth = (float)fmax(0.0, vec3_dot(sha->hit->normal, half));
	if ((float)sha->mat.shininess <= 2.5f)
		spec = (double)(ndoth * ndoth);
	else if ((float)sha->mat.shininess <= 5.5f)
		spec = (double)(ndoth * ndoth * ndoth * ndoth);
	else
		spec = (double)powf(ndoth, (float)sha->mat.shininess);
	*total = vec3_add(*total, vec3_scale(mat->emission,
				fmin(spec_val * spec, 2.0)));
}

void	add_emissive_lighting(t_shading *sha, t_scene *sc, t_vec3 *total)
{
	size_t			i;
	t_emissive_ref	ref;
	t_mesh			*m;
	t_vec3			ctr;

	i = 0;
	while (i < sc->emissive_n)
	{
		ref = sc->emissive_cache[i++];
		em_vol(sha, sc, total, ref);
		em_surf(sha, sc, total, ref);
		if (ref.type == TYPE_MESH)
		{
			m = &sc->meshes[ref.index];
			ctr = vec3_add(m->transform.pos, vec3_scale(
						vec3_add(m->bbox.min, m->bbox.max), 0.5));
			sha->aux_v = vec3_sub(ctr, sha->hit->point);
			sha->em_normal = vec3(0, 0, 0);
			ctr = vec3_scale(vec3_sub(m->bbox.max, m->bbox.min), 0.5);
			apply_em(sha, total, &sc->materials[m->mat_id], vec3_mag(ctr));
		}
	}
}

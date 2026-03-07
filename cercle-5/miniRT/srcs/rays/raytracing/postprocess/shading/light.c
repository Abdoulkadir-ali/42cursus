/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Inverse-square attenuation with adjustable constant to avoid
** blow-out at close range.  att = 1 / (1 + k * d^2)
*/
static double	light_attenuation(double dist_sq)
{
	return (1.0 / (1.0 + 0.05 * dist_sq));
}

static bool	light_visible(t_shading_ctx *ctx, t_light light, t_vec3 ld_norm,
		double dist, double ndotl)
{
	double	bias;

	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(ld_norm, -1.0),
			light.transform.forward) < light.cutoff)
		return (false);
	if (light.type == LIGHT_EMISSIVE)
		return (true);
	bias = fmax(EPSILON, EPSILON * 10.0 * (1.0 - ndotl));
	if (is_in_shadow(ctx->bvh, vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, bias)), ld_norm, dist))
		return (false);
	return (true);
}

/*
** Calculates lighting contribution for a single light source.
** Includes inverse-square distance attenuation.
*/
/*
** Calculates lighting contribution for a single light source.
** Standard directional/point lights are unattenuated (matches legacy miniRT).
*/
t_vec3	calc_light(t_shading_ctx *ctx, t_light light)
{
	t_vec3	ld;
	t_vec3	ld_norm;
	double	dist;
	double	ndotl;
	t_vec3	half;
	double	spec;

	ld = vec3_sub(light.transform.pos, ctx->hit->point);
	dist = vec3_mag(ld);
	if (dist < 1e-8)
		return (vec3(0, 0, 0));
	ld_norm = vec3_scale(ld, 1.0 / dist);
	ndotl = vec3_dot(ctx->hit->normal, ld_norm);
	if (ndotl <= 0.0)
		return (vec3(0, 0, 0));
	if (!light_visible(ctx, light, ld_norm, dist, ndotl))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(ld_norm,
				vec3_scale(ctx->ray->direction, -1.0)));
	spec = pow(fmax(0.0, vec3_dot(ctx->hit->normal, half)),
			ctx->mat.shininess);
	return (vec3_add(pixel_color(ctx->albedo, light.rgb, light.brightness
				* ndotl), vec3_scale(light.rgb, light.brightness
				* ctx->mat.specular * spec)));
}

static void	apply_emissive(t_shading_ctx *ctx, t_vec3 *total,
		t_material *mat, t_vec3 ld_rad)
{
	double	dist_surf;
	t_vec3	ldir;
	double	ndotl;
	double	att;
	double	bright;

	dist_surf = vec3_mag(ctx->aux_v) - ld_rad.x - 0.01;
	if (dist_surf <= 0.0)
		return ;
	ldir = vec3_norm(ctx->aux_v);
	ndotl = vec3_dot(ctx->hit->normal, ldir);
	if (ndotl <= 0.0)
		return ;
	if (is_in_shadow(ctx->bvh, vec3_add(ctx->hit->point, vec3_scale(
					ctx->hit->normal, fmax(EPSILON, EPSILON * 10 * (1 - ndotl)))),
			ldir, dist_surf))
		return ;
	att = light_attenuation(dist_surf * dist_surf);
	bright = vec3_mag(mat->emission) / 255.0 * fmax(ld_rad.x, 0.5) * 3.0;
	*total = vec3_add(*total, vec3_add(pixel_color(ctx->albedo, mat->emission,
					bright * ndotl * att), vec3_scale(mat->emission, bright
					* ctx->mat.specular * att * pow(fmax(0.0,
							vec3_dot(ctx->hit->normal, vec3_norm(vec3_add(ldir,
										vec3_scale(ctx->ray->direction,
											-1.0))))),
						ctx->mat.shininess))));
}

static void	add_sphere_emission(t_shading_ctx *ctx, t_scene *sc, t_vec3 *total)
{
	int			i;
	t_sphere	*sp;
	double		rad;

	i = -1;
	while (++i < sc->sphere_count)
	{
		sp = &sc->spheres[i];
		if (vec3_mag_sq(sc->materials[sp->mat_id].emission) > 1.0)
		{
			ctx->aux_v = vec3_sub(sp->transform.pos, ctx->hit->point);
			rad = fmax(fabs(sp->transform.scale.x), 1.0);
			rad *= sqrt(sp->radius_sq);
			apply_emissive(ctx, total, &sc->materials[sp->mat_id],
				vec3(rad, 0, 0));
		}
	}
}

void	add_emissive_lighting(t_shading_ctx *ctx, t_scene *sc, t_vec3 *total)
{
	int		i;
	t_mesh	*m;
	t_vec3	c;

	add_sphere_emission(ctx, sc, total);
	i = -1;
	while (++i < sc->mesh_count)
	{
		m = &sc->meshes[i];
		if (m->mat_id >= 0 && m->mat_id < sc->mat_count
			&& vec3_mag_sq(sc->materials[m->mat_id].emission) > 1.0)
		{
			c = vec3_add(m->transform.pos, vec3_scale(
						vec3_add(m->bbox.min, m->bbox.max), 0.5));
			ctx->aux_v = vec3_sub(c, ctx->hit->point);
			apply_emissive(ctx, total, &sc->materials[m->mat_id],
				vec3(vec3_mag(vec3_scale(
							vec3_sub(m->bbox.max, m->bbox.min), 0.5)), 0, 0));
		}
	}
}

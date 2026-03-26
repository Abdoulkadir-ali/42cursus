/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 02:32:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	setup_shading(t_shading *ctx, t_hit *hit, t_scene *scene,
		const t_bvh *bvh)
{
	float	r;

	ctx->hit = hit;
	ctx->scene = scene;
	ctx->bvh = bvh;
	get_material(ctx);
	ctx->albedo = sample_texture(&ctx->mat.albedo_map, hit->u, hit->v);
	if (ctx->mat.roughness_map.type == TEX_BITMAP)
		ctx->mat.roughness = sample_texture(&ctx->mat.roughness_map,
				hit->u, hit->v).x / COLOR_MAX;
	if (ctx->mat.metallic_map.type == TEX_BITMAP)
		ctx->mat.metallic = sample_texture(&ctx->mat.metallic_map,
				hit->u, hit->v).x / COLOR_MAX;
	r = 1.0f - (float)ctx->mat.roughness;
	ctx->mat.shininess = (double)(r * r * r * r) * SHININESS_SCALE
		+ SHININESS_OFFSET;
	ctx->mat.specular = ctx->mat.specular * (1.0 - ctx->mat.metallic
			* METALLIC_REDUCT) + ctx->mat.metallic * METALLIC_BOOST;
	apply_bump(ctx);
}

static t_vec3	compute_refraction(t_shading *ctx, const t_ray *ray,
		double *kr, double next_w)
{
	t_vec3	ref_dir;
	t_ray	ref_ray;
	double	ior;

	ior = 1.0 + (ctx->mat.refract_index / REFRACT_MAX_DEG) * REFRACT_IOR_SCALE;
	ref_dir = vec3_refract(ray->direction, ctx->hit->normal, ior);
	if (vec3_mag_sq(ref_dir) < MAG_EPSILON)
	{
		*kr = 1.0;
		return (vec3(0, 0, 0));
	}
	ray_init(&ref_ray, ctx->hit->point, ref_dir);
	ref_ray.depth = ray->depth + 1;
	ref_ray.weight = next_w;
	if (vec3_dot(ref_dir, ctx->hit->normal) > 0)
		ref_ray.origin = vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, SHADOW_BIAS));
	else
		ref_ray.origin = vec3_sub(ctx->hit->point,
				vec3_scale(ctx->hit->normal, SHADOW_BIAS));
	return (trace_ray(ctx->bvh, &ref_ray, ctx->scene));
}

static t_vec3	compute_reflection(t_shading *ctx, const t_ray *ray, double nw)
{
	t_vec3	ref_dir;
	t_ray	ref_ray;
	t_vec3	n;

	ref_dir = vec3_reflect(ray->direction, ctx->hit->normal);
	n = ctx->hit->normal;
	if (vec3_dot(ray->direction, ctx->hit->normal) > 0.0)
		n = vec3_scale(ctx->hit->normal, -1.0);
	ray_init(&ref_ray, vec3_add(ctx->hit->point, vec3_scale(n, SHADOW_BIAS)),
		ref_dir);
	ref_ray.depth = ray->depth + 1;
	ref_ray.weight = nw;
	return (trace_ray(ctx->bvh, &ref_ray, ctx->scene));
}

static void	apply_bounces(t_shading *ctx, t_vec3 *tot, double kr)
{
	double	nw;

	if (ctx->mat.transparency > 0.0)
	{
		nw = ctx->ray->weight * ctx->mat.transparency;
		if (nw > WEIGHT_MIN)
			*tot = vec3_add(vec3_scale(*tot, 1.0 - ctx->mat.transparency),
					vec3_scale(compute_refraction(ctx, ctx->ray, &kr, nw),
						ctx->mat.transparency));
	}
	if (kr > 0.0)
	{
		nw = ctx->ray->weight * kr;
		if (nw > WEIGHT_MIN)
			*tot = vec3_add(vec3_scale(*tot, 1.0 - kr),
					vec3_scale(compute_reflection(ctx, ctx->ray, nw), kr));
	}
}

t_vec3	compute_color(t_hit *hit, t_scene *sc, const t_bvh *bvh,
		const t_ray *r)
{
	t_shading	ctx;
	t_vec3		total;
	int			i;

	ctx.ray = r;
	setup_shading(&ctx, hit, sc, bvh);
	total = pixel_color(ctx.albedo, sc->ambient.rgb, sc->ambient.brightness);
	i = -1;
	if (r->depth < 2)
		while (++i < sc->light_count)
			total = vec3_add(total, calc_light(&ctx, sc->lights[i]));
	if (r->depth == 0)
		add_emissive_lighting(&ctx, sc, &total);
	total = vec3_add(total, ctx.mat.emission);
	if (r->depth >= MAX_DEPTH)
		return (clamp_color(total));
	apply_bounces(&ctx, &total, ctx.mat.reflectivity);
	return (clamp_color(total));
}

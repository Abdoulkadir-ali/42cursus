/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 22:22:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

#define MAX_DEPTH 5

static void	setup_shading(t_shading_ctx *ctx, t_hit *hit, t_scene *scene,
		const t_bvh *bvh)
{
	ctx->hit = hit;
	ctx->scene = scene;
	ctx->bvh = bvh;
	get_material(ctx);
	ctx->albedo = sample_texture(&ctx->mat.albedo_map, hit->u, hit->v);
	if (ctx->mat.roughness_map.type == TEX_BITMAP)
		ctx->mat.roughness = sample_texture(&ctx->mat.roughness_map,
				hit->u, hit->v).x / 255.0;
	if (ctx->mat.metallic_map.type == TEX_BITMAP)
		ctx->mat.metallic = sample_texture(&ctx->mat.metallic_map,
				hit->u, hit->v).x / 255.0;
	/* Map PBR fields into Blinn-Phong parameters used by calc_light */
	ctx->mat.shininess = (double)powf((float)(1.0f - (float)ctx->mat.roughness),
			4.0f) * 200.0 + 2.0;
	ctx->mat.specular  = ctx->mat.specular * (1.0 - ctx->mat.metallic * 0.5)
		+ ctx->mat.metallic * 0.9;
	apply_bump(ctx);
}

static t_vec3	compute_refraction(t_shading_ctx *ctx, const t_ray *ray,
		double *kr, double next_w)
{
	t_vec3	refracted_dir;
	t_ray	refracted_ray;
	t_vec3	refracted_color;

	/* refract_index stores degrees (0-180); convert to IOR ratio (1.0-3.0) */
	double	ior;

	ior = 1.0 + (ctx->mat.refract_index / 180.0) * 2.0;
	refracted_dir = vec3_refract(ray->direction, ctx->hit->normal, ior);
	if (vec3_mag_sq(refracted_dir) < 1e-6)
	{
		*kr = 1.0;
		return (vec3(0, 0, 0));
	}
	ray_init(&refracted_ray, ctx->hit->point, refracted_dir);
	refracted_ray.depth = ray->depth + 1;
	refracted_ray.weight = next_w;
	refracted_ray.origin = vec3_sub(ctx->hit->point,
			vec3_scale(ctx->hit->normal, 1e-4));
	if (vec3_dot(refracted_dir, ctx->hit->normal) > 0)
		refracted_ray.origin = vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, 1e-4));
	refracted_color = trace_ray(ctx->bvh, &refracted_ray, ctx->scene);
	return (refracted_color);
}

static t_vec3	compute_reflection(t_shading_ctx *ctx, const t_ray *ray, double next_w)
{
	t_vec3	reflected_dir;
	t_ray	reflected_ray;
	t_vec3	offset_normal;

	reflected_dir = vec3_reflect(ray->direction, ctx->hit->normal);
	offset_normal = ctx->hit->normal;
	if (vec3_dot(ray->direction, ctx->hit->normal) > 0.0)
		offset_normal = vec3_scale(ctx->hit->normal, -1.0);
	ray_init(&reflected_ray, vec3_add(ctx->hit->point,
			vec3_scale(offset_normal, 1e-4)), reflected_dir);
	reflected_ray.depth = ray->depth + 1;
	reflected_ray.weight = next_w;
	return (trace_ray(ctx->bvh, &reflected_ray, ctx->scene));
}

t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray)
{
	t_shading_ctx	ctx;
	t_vec3			total;
	double			kr;
	int				i;

	ctx.ray = ray;
	setup_shading(&ctx, hit, scene, bvh);
	total = pixel_color(ctx.albedo, scene->ambient.rgb,
			scene->ambient.brightness);
	i = 0;
	if (ray->depth < 2)
	{
		while (i < scene->light_count)
			total = vec3_add(total, calc_light(&ctx, scene->lights[i++]));
	}
	if (ray->depth == 0)
		add_emissive_lighting(&ctx, scene, &total);
	total = vec3_add(total, ctx.mat.emission);
	if (ray->depth >= MAX_DEPTH)
		return (clamp_color(total));
	kr = ctx.mat.reflectivity;
	if (ctx.mat.transparency > 0.0)
	{
		double next_w = ray->weight * ctx.mat.transparency;
		if (next_w > 0.02)
			total = vec3_add(vec3_scale(total, 1.0 - ctx.mat.transparency),
				vec3_scale(compute_refraction(&ctx, ray, &kr, next_w),
					ctx.mat.transparency));
	}
	if (kr > 0.0)
	{
		double next_w = ray->weight * kr;
		if (next_w > 0.02)
			total = vec3_add(vec3_scale(total, 1.0 - kr),
				vec3_scale(compute_reflection(&ctx, ray, next_w), kr));
	}
	return (clamp_color(total));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Computes the final shaded color for a hit point.
*/
static t_vec3	clamp_color(t_vec3 color)
{
	if (color.x < 0)
		color.x = 0;
	if (color.y < 0)
		color.y = 0;
	if (color.z < 0)
		color.z = 0;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

/*
** Scales and clamps a color value.
*/
t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = (obj.x / 255.0) * (light.x / 255.0) * intensity * 255.0;
	f.y = (obj.y / 255.0) * (light.y / 255.0) * intensity * 255.0;
	f.z = (obj.z / 255.0) * (light.z / 255.0) * intensity * 255.0;
	return (f);
}

#define MAX_DEPTH 5

t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray)
{
	t_shading_ctx	ctx;
	t_vec3			total;
	t_vec3			reflected_color;
	t_vec3			refracted_color;
	int				i;
	double			kr; /* Reflection coefficient (Fresnel) */

	ctx.hit = hit;
	ctx.scene = scene;
	ctx.bvh = bvh;
	ctx.ray = ray;
	get_material(&ctx);
	ctx.albedo = sample_texture(&ctx.mat.albedo_map, hit->u, hit->v);
	if (ctx.mat.roughness_map.type == TEX_BITMAP)
		ctx.mat.roughness = sample_texture(&ctx.mat.roughness_map, hit->u, hit->v).x / 255.0;
	if (ctx.mat.metallic_map.type == TEX_BITMAP)
		ctx.mat.metallic = sample_texture(&ctx.mat.metallic_map, hit->u, hit->v).x / 255.0;
	apply_bump(&ctx);
	
	/* 1. Local Illumination (Ambient + Diffuse/Spec) */
	total = pixel_color(ctx.albedo, scene->ambient.rgb,
			scene->ambient.brightness);
	i = 0;
	while (i < scene->light_count)
	{
		total = vec3_add(total, calc_light(&ctx, scene->lights[i]));
		i++;
	}

	/* 2. Recursion Limit */
	if (ray->depth >= MAX_DEPTH)
		return (clamp_color(total));

	/* 3. Reflection & Refraction */
	kr = ctx.mat.reflectivity;
	
	/* Simplified Fresnel for Dielectrics (Glass/Water) */
	if (ctx.mat.transparency > 0.0)
	{
		t_vec3	refracted_dir = vec3_refract(ray->direction, hit->normal, ctx.mat.refract_index);
		t_ray	refracted_ray;
		
		/* Check for Total Internal Reflection */
		if (vec3_mag_sq(refracted_dir) < 1e-6)
		{
			kr = 1.0; /* Full reflection */
		}
		else
		{
			/* Schlick approximation could go here, for now blend based on transparency */
			/* Actually, if transparency is high, we see through. */
			ray_init(&refracted_ray, hit->point, refracted_dir);
			/* Offset origin slightly to avoid self-intersection? 
			   Usually handled by t_min in trace, but let's be safe: 
			   Point is already on surface. Refract goes IN or OUT. 
			   Safe approach: ray_init with epsilon offset logic if needed, 
			   but our BVH/trace handles t > epsilon. */
			refracted_ray.depth = ray->depth + 1;
			// Manual offset to prevent self-intersection acne
			refracted_ray.origin = vec3_sub(hit->point, vec3_scale(hit->normal, 1e-4));
			if (vec3_dot(refracted_dir, hit->normal) > 0) /* Leaving */
				refracted_ray.origin = vec3_add(hit->point, vec3_scale(hit->normal, 1e-4));

			refracted_color = trace_ray(bvh, &refracted_ray, scene);
			/* Mix Refracted with Local Color based on Transparency */
			// total = vec3_lerp(total, refracted_color, ctx.mat.transparency);
			// For glass, local color is usually tint.
			total = vec3_add(vec3_scale(total, 1.0 - ctx.mat.transparency), 
							 vec3_scale(refracted_color, ctx.mat.transparency));
		}
	}

	/* 4. Reflection (Metal or Fresnel from Dielectric) */
	if (kr > 0.0)
	{
		t_vec3	reflected_dir = vec3_reflect(ray->direction, hit->normal);
		t_ray	reflected_ray;

		ray_init(&reflected_ray, vec3_add(hit->point, vec3_scale(hit->normal, 1e-4)), reflected_dir);
		reflected_ray.depth = ray->depth + 1;
		reflected_color = trace_ray(bvh, &reflected_ray, scene);
		total = vec3_add(vec3_scale(total, 1.0 - kr), vec3_scale(reflected_color, kr));
	}

	return (clamp_color(total));
}

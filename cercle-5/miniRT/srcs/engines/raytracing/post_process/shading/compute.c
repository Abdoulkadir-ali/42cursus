/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 12:33:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	add_gi(t_shading *sha, const t_ray *ray, t_vec3 *total)
{
	t_vec3	gi;

	if (sha->opts && !sha->opts->gi_enabled)
		return ;
	if (sha->mat.transparency >= 0.5)
		return ;
	gi = compute_indirect(sha, ray);
	if (sha->opts && sha->opts->gi_strength > 0.0)
		gi = vec3_scale(gi, sha->opts->gi_strength);
	*total = vec3_add(*total, gi);
}

static double	compute_fresnel(t_shading *sha, double kr)
{
	double	f0;
	double	fresnel;

	if (sha->opts && !sha->opts->fresnel_enabled)
		return (kr);
	f0 = sha->mat.metallic * 0.9 + (1.0 - sha->mat.metallic) * 0.04;
	fresnel = f0 + (1.0 - f0) * pow(1.0 - sha->cache.ndotv, 5.0);
	return (fmin(kr + fresnel * (1.0 - kr), 1.0));
}

static void	recursive_color(t_shading *sha, const t_ray *ray, t_vec3 *total)
{
	double	next_w;
	double	kr;
	double	fresnel;

	add_gi(sha, ray, total);
	kr = sha->mat.reflectivity;
	fresnel = compute_fresnel(sha, kr);
	if (sha->mat.transparency > 0.0)
	{
		next_w = ray->weight * sha->mat.transparency;
		if (next_w > 0.02)
			*total = vec3_add(*total,
					vec3_scale(compute_refraction(sha, ray, &kr, next_w),
						sha->mat.transparency * (1.0 - fresnel)));
	}
	if (kr > 0.0)
	{
		next_w = ray->weight * kr;
		if (next_w > 0.02)
			*total = vec3_add(*total,
					vec3_scale(compute_reflection(sha, ray, next_w), kr));
	}
}

static void	add_emission(t_shading *sha, t_vec3 *total)
{
	double	scale;

	if (vec3_mag_sq(sha->mat.emission) <= 0.0)
		return ;
	scale = sha->mat.em_intensity / 255.0;
	*total = vec3_add(*total, vec3(sha->mat.emission.x * scale,
				sha->mat.emission.y * scale,
				sha->mat.emission.z * scale));
}

__attribute__((optimize("O3")))
t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray)
{
	t_shading	sha;
	t_vec3		total;
	size_t		i;

	sha.ray = ray;
	setup_shading(&sha, hit, scene, bvh);
	total = vec3_scale(pixel_color(sha.albedo, scene->ambient.rgb,
				scene->ambient.brightness), compute_ao(&sha));
	if (ray->depth == 0 || (sha.opts && sha.opts->lights_on_bounces))
	{
		i = 0;
		while (i < scene->light_count)
			total = vec3_add(total, calc_light(&sha, scene->lights[i++]));
		// add_emissive_lighting(&sha, scene, &total);
	}
	add_emission(&sha, &total);
	if (ray->depth < MAX_DEPTH)
		recursive_color(&sha, ray, &total);
	return (clamp_color(total, sha.opts));
}

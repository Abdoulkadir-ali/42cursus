/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 02:01:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

#define AO_SAMPLES	8
#define AO_RADIUS	0.8
#define AO_STRENGTH	0.65

static double	compute_ao(const t_shading *sha)
{
	uint32_t	seed;
	t_vec3		origin;
	t_vec3		dir;
	t_ray		ao_ray;
	int			hits;
	int			i;
	int			samples;
	double		radius;

	if (!sha->opts || !sha->opts->ao_enabled)
		return (1.0);
	if (sha->mat.transparency > 0.5)
		return (1.0);
	samples = (sha->opts->ao_samples > 0) ? sha->opts->ao_samples : AO_SAMPLES;
	radius = (sha->opts->ao_radius > 0.0) ? sha->opts->ao_radius : AO_RADIUS;
	seed = (uint32_t)((int64_t)(sha->hit->point.x * 73856093)
			^ (int64_t)(sha->hit->point.y * 19349663)
			^ (int64_t)(sha->hit->point.z * 83492791)
			^ (int64_t)(sha->frame_idx * 1664525));
	origin = vec3_add(sha->hit->point,
			vec3_scale(sha->hit->normal, EPSILON * 20.0));
	hits = 0;
	i = 0;
	while (i < samples)
	{
		dir = rt_random_on_hemisphere(sha->hit->normal, &seed);
		ray_init(&ao_ray, origin, dir);
		if (bvh_occluded(sha->bvh, &ao_ray, radius))
			hits++;
		i++;
	}
	if (!sha->opts->ao_strength)
		return (1.0 - AO_STRENGTH * ((double)hits / samples));
	return (1.0 - sha->opts->ao_strength * ((double)hits / samples));
}

static void	setup_shading(t_shading *sha, t_hit *hit, t_scene *scene,
		const t_bvh *bvh)
{
	float	r;

	sha->hit = hit;
	sha->scene = scene;
	sha->bvh = bvh;
	sha->opts = scene->opts;
	sha->frame_idx = sha->ray->frame_idx;
	get_material(sha);
	sha->albedo = sample_texture(&sha->mat.albedo_map, hit->u, hit->v);
	if (sha->mat.roughness_map.type == TEX_BITMAP)
		sha->mat.roughness = sample_texture(&sha->mat.roughness_map,
				hit->u, hit->v).x / 255.0;
	if (sha->mat.metallic_map.type == TEX_BITMAP)
		sha->mat.metallic = sample_texture(&sha->mat.metallic_map,
				hit->u, hit->v).x / 255.0;
	r = 1.0f - (float)sha->mat.roughness;
	sha->mat.shininess = (double)r * r * r * r * 200.0 + 2.0;
	sha->mat.specular = sha->mat.specular * (1.0 - sha->mat.metallic * 0.5)
		+ sha->mat.metallic * 0.9;
	apply_bump(sha);
}

static t_vec3	refract_channel(t_shading *sha, const t_ray *ray,
		double ior, double next_w)
{
	t_vec3	dir;
	t_ray	r;
	t_vec3	c;

	dir = vec3_refract(ray->direction, sha->hit->normal, ior);
	if (vec3_mag_sq(dir) < 1e-6)
		return (vec3(0, 0, 0));
	ray_init(&r, sha->hit->point, dir);
	r.depth = ray->depth + 1;
	r.weight = next_w;
	r.frame_idx = ray->frame_idx;
	r.origin = vec3_sub(sha->hit->point, vec3_scale(sha->hit->normal, 1e-4));
	if (vec3_dot(dir, sha->hit->normal) > 0)
		r.origin = vec3_add(sha->hit->point, vec3_scale(sha->hit->normal, 1e-4));
	c = trace_ray(sha->bvh, &r, sha->scene);
	return (c);
}

static t_vec3	compute_refraction(t_shading *sha, const t_ray *ray,
		double *kr, double next_w)
{
	t_vec3	c_r;
	t_vec3	c_g;
	t_vec3	c_b;
	double	ior;
	double	disp;

	ior = sha->mat.refract_index;
	disp = (sha->opts && sha->opts->chroma_enabled)
		? sha->opts->chroma_dispersion
		: 0.0;
	c_g = refract_channel(sha, ray, ior, next_w);
	if (vec3_mag_sq(c_g) < 1e-8 && *kr == 1.0)
		return (vec3(0, 0, 0));
	if (disp > 1e-6)
	{
		c_r = refract_channel(sha, ray, ior - disp, next_w);
		c_b = refract_channel(sha, ray, ior + disp, next_w);
		return (vec3(c_r.x, c_g.y, c_b.z));
	}
	return (c_g);
}

static t_vec3	compute_reflection(t_shading *sha, const t_ray *ray,
		double next_w)
{
	t_vec3		reflected_dir;
	t_ray		reflected_ray;
	uint32_t	seed;

	reflected_dir = vec3_reflect(ray->direction, sha->hit->normal);
	if (sha->mat.roughness > 0.001)
	{
		seed = (uint32_t)(sha->frame_idx * 1664525) + 1013904223;
		seed ^= (uint32_t)(sha->hit->point.x * 123.4)
			^ (uint32_t)(sha->hit->point.y * 567.8);
		reflected_dir = vec3_norm(vec3_add(reflected_dir,
					vec3_scale(rt_random_on_sphere(&seed),
						sha->mat.roughness * 0.5)));
	}
	ray_init(&reflected_ray, vec3_add(sha->hit->point,
			vec3_scale(sha->hit->normal, 1e-4)), reflected_dir);
	if (vec3_dot(reflected_dir, sha->hit->normal) < 0.0)
		ray_init(&reflected_ray, vec3_sub(sha->hit->point,
				vec3_scale(sha->hit->normal, 1e-4)), reflected_dir);
	reflected_ray.depth = ray->depth + 1;
	reflected_ray.weight = next_w;
	reflected_ray.frame_idx = sha->frame_idx;
	return (trace_ray(sha->bvh, &reflected_ray, sha->scene));
}

static t_vec3	compute_indirect(t_shading *sha, const t_ray *ray)
{
	t_ray		gi_ray;
	uint32_t	seed;
	t_vec3		dir;
	t_vec3		indirect;

	if (ray->depth >= MAX_DEPTH - 1)
		return (vec3(0, 0, 0));
	if (sha->mat.transparency > 0.5)
		return (vec3(0, 0, 0));
	seed = (uint32_t)(sha->frame_idx * 1664525) + 1013904223;
	seed ^= (uint32_t)(sha->hit->point.x * 123.0) ^ (uint32_t)(sha->hit->point.z * 456.0);
	dir = rt_random_cosine_weighted(sha->hit->normal, &seed);
	ray_init(&gi_ray, vec3_add(sha->hit->point,
			vec3_scale(sha->hit->normal, 1e-3)), dir);
	gi_ray.depth = MAX_DEPTH - 1;
	gi_ray.weight = ray->weight * 0.4;
	gi_ray.frame_idx = sha->frame_idx;
	indirect = trace_ray(sha->bvh, &gi_ray, sha->scene);
	if (vec3_mag_sq(indirect) < 1e-4 && sha->scene->ambient.brightness > 0.0)
		indirect = vec3_scale(sha->scene->ambient.rgb,
				sha->scene->ambient.brightness * 0.5);
	indirect.x = fmin(indirect.x, 255.0);
	indirect.y = fmin(indirect.y, 255.0);
	indirect.z = fmin(indirect.z, 255.0);
	return (pixel_color(sha->albedo, indirect, 0.5));
}

static void	recursive_color(t_shading *sha, const t_ray *ray, t_vec3 *total)
{
	double	next_w;
	double	kr;
	t_vec3	refr;
	double	cos_theta;
	double	f0;
	double	fresnel;

	(void)cos_theta;
	(void)f0;
	fresnel = 0.0;
	if ((!sha->opts || sha->opts->gi_enabled) && sha->mat.transparency < 0.5)
	{
		t_vec3	gi = compute_indirect(sha, ray);
		if (sha->opts && sha->opts->gi_strength > 0.0)
			gi = vec3_scale(gi, sha->opts->gi_strength);
		*total = vec3_add(*total, gi);
	}
	kr = sha->mat.reflectivity;
	if (!sha->opts || sha->opts->fresnel_enabled)
	{
		cos_theta = fmax(0.0, -vec3_dot(ray->direction, sha->hit->normal));
		f0 = sha->mat.metallic * 0.9 + (1.0 - sha->mat.metallic) * 0.04;
		fresnel = f0 + (1.0 - f0) * pow(1.0 - cos_theta, 5.0);
		kr = fmin(kr + fresnel * (1.0 - kr), 1.0);
	}
	if (sha->mat.transparency > 0.0)
	{
		next_w = ray->weight * sha->mat.transparency;
		if (next_w > 0.02)
		{
			refr = compute_refraction(sha, ray, &kr, next_w);
			*total = vec3_add(*total,
					vec3_scale(refr, sha->mat.transparency * (1.0 - fresnel)));
		}
	}
	if (kr > 0.0)
	{
		next_w = ray->weight * kr;
		if (next_w > 0.02)
			*total = vec3_add(*total,
					vec3_scale(compute_reflection(sha, ray, next_w), kr));
	}
}

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
	i = 0;
	while (i < scene->light_count)
		total = vec3_add(total, calc_light(&sha, scene->lights[i++]));
	add_emissive_lighting(&sha, scene, &total);
	if (vec3_mag_sq(sha.mat.emission) > 0.0)
	{
		double	scale = sha.mat.em_intensity / 255.0;
		total = vec3_add(total, vec3(sha.mat.emission.x * scale,
				sha.mat.emission.y * scale,
				sha.mat.emission.z * scale));
	}
	if (ray->depth < MAX_DEPTH)
		recursive_color(&sha, ray, &total);
	return (clamp_color(total, sha.opts));
}

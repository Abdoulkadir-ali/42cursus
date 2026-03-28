/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:38:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	setup_shading(t_shading *sha, t_hit *hit, t_rt_engine *rt)
{
	sha->hit = hit;
	sha->rt = rt;
	sha->mat = &rt->rt_materials[hit->mat_idx];
	if (sha->mat->albedo_tex_idx >= 0)
		sha->albedo = sample_texture_pool(sha, sha->mat->albedo_tex_idx, hit->u,
				hit->v);
	else
		sha->albedo = sha->mat->color;
	apply_bump(sha);
}

static t_vec3	compute_refraction(t_shading *sha, const t_ray *ray, double *kr,
		double next_w)
{
	t_vec3	ref_dir;
	t_ray	ref_ray;
	double	ior;

	ior = 1.0 + (sha->mat->refract_index / 100.0) * 1.5;
		/* Constants should be defined safely */
	ref_dir = vec3_refract(ray->direction, sha->hit->normal, ior);
	if (vec3_mag_sq(ref_dir) < 1e-6)
	{
		*kr = 1.0;
		return (vec3(0, 0, 0));
	}
	ray_init(&ref_ray, sha->hit->point, ref_dir);
	ref_ray.depth = ray->depth + 1;
	ref_ray.weight = next_w;
	if (vec3_dot(ref_dir, sha->hit->normal) > 0)
		ref_ray.origin = vec3_add(sha->hit->point, vec3_scale(sha->hit->normal,
					sha->rt->settings.shadow_bias));
	else
		ref_ray.origin = vec3_sub(sha->hit->point, vec3_scale(sha->hit->normal,
					sha->rt->settings.shadow_bias));
	return (trace_ray((t_rt_engine *)sha->rt, &ref_ray));
}

static t_vec3	compute_reflection(t_shading *sha, const t_ray *ray, double nw)
{
	t_vec3	ref_dir;
	t_ray	ref_ray;
	t_vec3	n;

	ref_dir = vec3_reflect(ray->direction, sha->hit->normal);
	n = sha->hit->normal;
	if (vec3_dot(ray->direction, sha->hit->normal) > 0.0)
		n = vec3_scale(sha->hit->normal, -1.0);
	ray_init(&ref_ray, vec3_add(sha->hit->point, vec3_scale(n,
				sha->rt->settings.shadow_bias)), ref_dir);
	ref_ray.depth = ray->depth + 1;
	ref_ray.weight = nw;
	return (trace_ray((t_rt_engine *)sha->rt, &ref_ray));
}

static void	apply_bounces(t_shading *sha, t_vec3 *tot, double kr)
{
	double	nw;

	if (sha->mat->transparency > 0.0)
	{
		nw = sha->ray->weight * sha->mat->transparency;
		if (nw > 0.001)
			*tot = vec3_add(vec3_scale(*tot, 1.0 - sha->mat->transparency),
					vec3_scale(compute_refraction(sha, sha->ray, &kr, nw),
						sha->mat->transparency));
	}
	if (kr > 0.0)
	{
		nw = sha->ray->weight * kr;
		if (nw > 0.001)
			*tot = vec3_add(vec3_scale(*tot, 1.0 - kr),
					vec3_scale(compute_reflection(sha, sha->ray, nw), kr));
	}
}

t_vec3	compute_color(t_hit *hit, t_rt_engine *rt, const t_ray *r)
{
	t_shading	sha;
	t_vec3		total;
	size_t		i;

	sha.ray = r;
	setup_shading(&sha, hit, rt);
	total = pixel_color(sha.albedo, rt->scene->ambient.rgb,
			rt->scene->ambient.brightness);
	i = 0;
	if (r->depth < 2)
		while (i < rt->scene->light_count)
			total = vec3_add(total, calc_light(&sha, rt,
						rt->scene->lights[i++]));
	if (r->depth == 0)
		add_emissive_lighting(&sha, rt, &total);
	total = vec3_add(total, sha.mat->emission);
	if (r->depth >= rt->settings.max_depth)
		return (clamp_color(total));
	apply_bounces(&sha, &total, sha.mat->reflectivity);
	return (clamp_color(total));
}

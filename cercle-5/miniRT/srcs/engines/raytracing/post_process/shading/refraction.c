/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:04:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_ray	build_refract_ray(t_shading *sha, const t_ray *ray, double ior,
		double next_w)
{
	t_vec3	dir;
	t_ray	r;

	dir = vec3_refract(ray->direction, sha->hit->normal, ior);
	ray_init(&r, sha->hit->point, dir);
	r.depth = ray->depth + 1;
	r.weight = next_w;
	r.frame_idx = ray->frame_idx;
	r.origin = vec3_sub(sha->hit->point, vec3_scale(sha->hit->normal, 1e-4));
	if (vec3_dot(dir, sha->hit->normal) > 0)
		r.origin = vec3_add(sha->hit->point,
				vec3_scale(sha->hit->normal, 1e-4));
	return (r);
}

static t_vec3	refract_channel(t_shading *sha, const t_ray *ray,
		double ior, double next_w)
{
	t_vec3	dir;
	t_ray	r;

	dir = vec3_refract(ray->direction, sha->hit->normal, ior);
	if (vec3_mag_sq(dir) < 1e-6)
		return (vec3(0, 0, 0));
	r = build_refract_ray(sha, ray, ior, next_w);
	return (trace_ray(sha->bvh, &r, sha->scene));
}

t_vec3	compute_refraction(t_shading *sha, const t_ray *ray,
		double *kr, double next_w)
{
	t_vec3	c_r;
	t_vec3	c_g;
	t_vec3	c_b;
	double	ior;
	double	disp;

	ior = sha->mat.refract_index;
	disp = 0.0;
	if (sha->opts && sha->opts->chroma_enabled)
		disp = sha->opts->chroma_dispersion;
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

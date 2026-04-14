/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ao.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:14:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

#define AO_SAMPLES	8
#define AO_RADIUS	0.8
#define AO_STRENGTH	0.65

static double	compute_ao_ray(const t_shading *sha, t_ray *ray, double rad)
{
	t_hit	hit;
	double	min_t;
	size_t	i;

	min_t = rad;
	hit.t = rad;
	if (bvh_intersect(sha->bvh, ray, &hit))
		min_t = hit.t;
	i = 0;
	while (i < sha->scene->plane_count)
	{
		if (intersect_plane(ray, &sha->scene->planes[i], &hit))
			if (hit.t < min_t)
				min_t = hit.t;
		i++;
	}
	if (min_t < rad)
		return (1.0 - (min_t / rad));
	return (0.0);
}

static void	init_ao_params(const t_shading *sha, int *samples, double *radius,
		double *strength)
{
	if (sha->opts->ao_samples <= 0)
		*samples = 16;
	else
		*samples = sha->opts->ao_samples;
	if (sha->opts->ao_radius <= 0.0)
		*radius = AO_RADIUS;
	else
		*radius = sha->opts->ao_radius;
	if (sha->opts->ao_strength > 0.0)
		*strength = sha->opts->ao_strength;
	else
		*strength = AO_STRENGTH;
}

static double	run_ao_samples(const t_shading *sha, int samples, double radius)
{
	uint32_t	seed;
	t_vec3		origin;
	t_ray		ao_ray;
	double		occ;
	int			i;

	seed = (uint32_t)((int64_t)(sha->hit->point.x * 73856093)
			^ (int64_t)(sha->hit->point.y * 19349663)
			^ (int64_t)(sha->hit->point.z * 83492791)
			^ (int64_t)(sha->frame_idx * 1103515245));
	origin = vec3_add(sha->hit->point, vec3_scale(sha->hit->normal, 1e-4));
	occ = 0.0;
	i = 0;
	while (i++ < samples)
	{
		ray_init(&ao_ray, origin,
			rt_random_cosine_weighted(sha->hit->normal, &seed));
		occ += compute_ao_ray(sha, &ao_ray, radius);
	}
	return (occ);
}

double	compute_ao(const t_shading *sha)
{
	int		samples;
	double	radius;
	double	strength;

	if (!sha->opts || !sha->opts->ao_enabled || sha->mat.transparency > 0.5)
		return (1.0);
	init_ao_params(sha, &samples, &radius, &strength);
	return (1.0 - strength * (run_ao_samples(sha, samples, radius) / samples));
}

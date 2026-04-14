/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:04:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static uint32_t	build_gi_seed(const t_shading *sha)
{
	uint32_t	seed;

	seed = (uint32_t)((int64_t)(sha->hit->point.x * 73856093)
			^ (int64_t)(sha->hit->point.y * 19349663)
			^ (int64_t)(sha->hit->point.z * 83492791));
	seed = (seed ^ (seed >> 16)) * 0x45d9f3b;
	seed = (seed ^ (seed >> 16)) * 0x45d9f3b;
	seed ^= (uint32_t)(sha->frame_idx * 1103515245 + 12345);
	seed ^= seed >> 16;
	return (seed);
}

t_vec3	compute_indirect(t_shading *sha, const t_ray *ray)
{
	t_ray		gi_ray;
	uint32_t	seed;
	t_vec3		dir;
	t_vec3		indirect;

	if (ray->depth >= MAX_DEPTH - 1 || sha->mat.transparency > 0.5)
		return (vec3(0, 0, 0));
	seed = build_gi_seed(sha);
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

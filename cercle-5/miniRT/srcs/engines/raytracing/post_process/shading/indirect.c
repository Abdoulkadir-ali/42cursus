/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 15:18:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

t_vec3	compute_indirect(t_shading *sha, const t_ray *ray)
{
	t_ray		gi_ray;
	uint64_t	seed;
	t_vec3		dir;
	t_vec3		indirect;

	if (ray->depth >= MAX_DEPTH - 1 || sha->mat.transparency > 0.5)
		return (vec3(0, 0, 0));
	seed = rt_seed_mix(sha->cache.seed_pos, (int)sha->frame_idx, 42);
	dir = rt_random_cosine_weighted(sha->hit->normal, &seed);
	ray_init(&gi_ray, sha->cache.org, dir);
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

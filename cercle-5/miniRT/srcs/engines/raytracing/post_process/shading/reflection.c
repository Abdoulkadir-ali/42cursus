/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 15:18:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	jitter_reflected(t_shading *sha, t_vec3 dir)
{
	uint64_t	seed;

	seed = rt_seed_mix(sha->cache.seed_pos, (int)sha->frame_idx, 1);
	return (vec3_norm(vec3_add(dir,
				vec3_scale(rt_random_on_sphere(&seed),
					sha->mat.roughness * 0.5))));
}

t_vec3	compute_reflection(t_shading *sha, const t_ray *ray, double next_w)
{
	t_vec3	reflected_dir;
	t_ray	reflected_ray;

	reflected_dir = vec3_reflect(ray->direction, sha->hit->normal);
	if (sha->mat.roughness > 0.001)
		reflected_dir = jitter_reflected(sha, reflected_dir);
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

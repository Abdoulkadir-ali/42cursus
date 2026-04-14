/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:04:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	jitter_reflected(t_shading *sha, t_vec3 dir)
{
	uint32_t	seed;

	seed = (uint32_t)(sha->frame_idx * 1103515245) + 12345;
	seed ^= (uint32_t)(sha->hit->point.x * 73856093)
		^ (uint32_t)(sha->hit->point.y * 19349663);
	seed = (seed ^ (seed >> 16)) * 0x45d9f3b;
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

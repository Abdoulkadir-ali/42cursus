/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Computes inverse direction and sign bits for a ray.
*/
static inline void	ray_compute_inv(t_ray *ray)
{
	ray->inv_dir = vec3(1.0 / ray->direction.x, 1.0 / ray->direction.y,
			1.0 / ray->direction.z);
	ray->sign[0] = (ray->inv_dir.x < 0);
	ray->sign[1] = (ray->inv_dir.y < 0);
	ray->sign[2] = (ray->inv_dir.z < 0);
}

/*
** Initializes a ray with the given origin and direction.
*/
void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
	ray_compute_inv(ray);
}

/*
** Normalizes the direction vector of a ray.
*/
void	ray_normalize_direction(t_ray *ray)
{
	ray->direction = vec3_norm(ray->direction);
	ray_compute_inv(ray);
}

/*
** Primary raytracing function.
** Intersects ray with BVH and planes, then computes color.
*/
t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene)
{
	t_hit	hit;
	t_hit	plane_hit;
	bool	hit_any;
	int		i;

	hit_any = bvh_intersect(bvh, ray, &hit);
	i = 0;
	while (i < scene->plane_count)
	{
		if (intersect_plane(ray, &scene->planes[i], &plane_hit))
		{
			if (!hit_any || plane_hit.t < hit.t)
			{
				hit = plane_hit;
				hit.ref.type = TYPE_PLANE;
				hit.ref.index = i;
				hit_any = true;
			}
		}
		i++;
	}
	if (hit_any)
		return (compute_color(&hit, scene, bvh, ray, 0));
	return (vec3(0, 0, 0));
}

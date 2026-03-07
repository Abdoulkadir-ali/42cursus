/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Clamp near-zero to tiny epsilon so 1/d stays finite (avoids inf*0 = NaN
** inside aabb_intersect_fast under -ffast-math / -ffinite-math-only).
*/
static inline double	safe_rcp(double d)
{
	if (d < 1e-20 && d > -1e-20)
	{
		if (d >= 0.0)
			return (1.0 / 1e-20);
		return (1.0 / -1e-20);
	}
	return (1.0 / d);
}

/*
** Computes inverse direction and sign bits for a ray.
*/
static inline void	ray_compute_inv(t_ray *ray)
{
	ray->inv_dir = vec3(safe_rcp(ray->direction.x),
			safe_rcp(ray->direction.y), safe_rcp(ray->direction.z));
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
	ray->depth = 0;
	ray->weight = 1.0;
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
	t_hit	temp_hit;
	bool	hit_any;
	int		i;

	hit.t = 1e30;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
	hit_any = bvh_intersect(bvh, ray, &hit);
	if (!hit_any)
		hit.t = 1e30;

	/* Check planes globally */
	if (scene)
	{
		i = 0;
		while (i < scene->plane_count)
		{
			if (intersect_plane(ray, &scene->planes[i], &temp_hit))
			{
				if (temp_hit.t < hit.t)
				{
					hit = temp_hit;
					hit.ref.type = TYPE_PLANE;
					hit.ref.index = i;
					hit_any = true;
				}
			}
			i++;
		}
	}

	if (hit_any)
		return (compute_color(&hit, scene, bvh, ray));
	return (vec3(0, 0, 0));
}

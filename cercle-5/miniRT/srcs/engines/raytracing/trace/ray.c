/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	safe_rcp(double d)
{
	double	ad;

	ad = __builtin_fabs(d);
	if (__builtin_expect(ad < 1e-20, 0))
		d = __builtin_copysign(1e-20, d);
	return (1.0 / d);
}

static void	ray_compute_inv(t_ray *ray)
{
	ray->inv_dir = vec3(safe_rcp(ray->direction.x),
			safe_rcp(ray->direction.y), safe_rcp(ray->direction.z));
	ray->sign[0] = (ray->inv_dir.x < 0);
	ray->sign[1] = (ray->inv_dir.y < 0);
	ray->sign[2] = (ray->inv_dir.z < 0);
}

void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
	ray->depth = 0;
	ray->weight = 1.0;
	ray->frame_idx = 0;
	ray_compute_inv(ray);
}

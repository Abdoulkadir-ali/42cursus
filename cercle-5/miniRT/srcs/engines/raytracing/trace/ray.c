/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raynorm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	safe_rcp(double d)
{
	double	ad;
	double	nd;

	ad = fabs(d);
	if (ad < SAFE_RCP_MIN)
	{
		if (d >= 0.0)
			nd = SAFE_RCP_MIN;
		else
			nd = -SAFE_RCP_MIN;
		return (1.0 / nd);
	}
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
	ray_compute_inv(ray);
	DBG_TRACE_MSG(DBG_CH_RENDER,
		"ray_init: depth=%d w=%.3f o=(%.2f,%.2f,%.2f)\n",
		ray->depth, ray->weight,
		ray->origin.x, ray->origin.y, ray->origin.z);
}


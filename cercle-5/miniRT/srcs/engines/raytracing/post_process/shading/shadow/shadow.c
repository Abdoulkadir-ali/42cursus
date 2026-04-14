/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static inline double	s_rcp(double d)
{
	if (__builtin_fabs(d) < 1e-20)
		d = __builtin_copysign(1e-20, d);
	return (1.0 / d);
}

static void	shadow_ray_init(t_ray *ray, t_vec3 origin, t_vec3 dir)
{
	ray->origin = origin;
	ray->direction = dir;
	ray->inv_dir = vec3(s_rcp(dir.x), s_rcp(dir.y), s_rcp(dir.z));
	ray->sign[0] = (ray->inv_dir.x < 0);
	ray->sign[1] = (ray->inv_dir.y < 0);
	ray->sign[2] = (ray->inv_dir.z < 0);
}

bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist)
{
	t_ray	sray;

	shadow_ray_init(&sray, p, ldir_norm);
	return (bvh_occluded(bvh, &sray, dist));
}

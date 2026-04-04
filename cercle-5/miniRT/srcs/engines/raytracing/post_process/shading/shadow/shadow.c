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

static bool	plane_shadows(const t_bvh *bvh, const t_ray *sray, double dist)
{
	t_vec3	oc;
	double	ndotd;
	double	t;
	size_t	i;

	i = 0;
	while (i < bvh->scene->plane_count)
	{
		ndotd = vec3_dot(bvh->scene->planes[i].transform.forward,
				sray->direction);
		if (fabs(ndotd) > 1e-6)
		{
			oc = vec3_sub(bvh->scene->planes[i].transform.pos,
					sray->origin);
			t = vec3_dot(oc,
					bvh->scene->planes[i].transform.forward) / ndotd;
			if (t > 0.001 && t < dist)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist)
{
	t_ray	sray;

	shadow_ray_init(&sray, p, ldir_norm);
	if (bvh_occluded4(bvh, &sray, dist))
		return (true);
	return (plane_shadows(bvh, &sray, dist));
}

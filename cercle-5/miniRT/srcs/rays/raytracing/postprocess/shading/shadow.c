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

static bool	plane_shadows(const t_bvh *bvh, const t_ray *sray, double dist)
{
	t_hit	hit;
	int		i;

	if (!bvh || !bvh->scene)
		return (false);
	i = 0;
	while (i < bvh->scene->plane_count)
	{
		if (intersect_plane(sray, &bvh->scene->planes[i], &hit))
		{
			if (hit.t > 0.001 && hit.t < dist)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist)
{
	t_ray	shadow_ray;

	ray_init(&shadow_ray, p, ldir_norm);
	if (bvh_occluded(bvh, &shadow_ray, dist))
		return (true);
	return (plane_shadows(bvh, &shadow_ray, dist));
}

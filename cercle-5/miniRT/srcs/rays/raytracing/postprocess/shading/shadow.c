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

/*
** Checks if a point is in shadow for a given light source.
*/
bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir)
{
	t_ray	shadow_ray;
	double	dist;

	dist = vec3_mag(ldir);
	ray_init(&shadow_ray, p, vec3_norm(ldir));
	if (bvh_occluded(bvh, &shadow_ray, dist))
		return (true);

	/* Check planes globally */
	if (bvh && bvh->scene)
	{
		t_hit	hit;
		int		i = 0;
		while (i < bvh->scene->plane_count)
		{
			if (intersect_plane(&shadow_ray, &bvh->scene->planes[i], &hit))
			{
				if (hit.t > 0.001 && hit.t < dist)
					return (true);
			}
			i++;
		}
	}
	return (false);
}

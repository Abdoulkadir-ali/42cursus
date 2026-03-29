/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	plane_shadows(const t_bvh *bvh, const t_ray *sray, double dist)
{
	int		i;
	t_hit	hit;
	t_scene	*scene;

	if (!bvh || !bvh->scene)
		return (false);
	scene = bvh->scene;
	i = -1;
	while (++i < (int)scene->plane_count)
	{
		if (intersect_plane(sray, &scene->primitives, scene->plane_indices[i], &hit))
		{
			if (hit.t > 0.001 && hit.t < dist)
				return (true);
		}
	}
	return (false);
}

bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist)
{
	t_ray	shadow_ray;
	bool	result;

	DBG_ENTER("is_in_shadow");
	DBG_TRACE_MSG(DBG_CH_RENDER,
		"is_in_shadow: o=(%.2f,%.2f,%.2f) dist=%.3f\n",
		p.x, p.y, p.z, dist);
	ray_init(&shadow_ray, p, ldir_norm);
	result = bvh_occluded(bvh, &shadow_ray, dist)
		|| plane_shadows(bvh, &shadow_ray, dist);
	if (result)
		DBG_TRACE_MSG(DBG_CH_RENDER, "is_in_shadow: OCCLUDED\n");
	else
		DBG_TRACE_MSG(DBG_CH_RENDER, "is_in_shadow: CLEAR\n");
	DBG_LEAVE("is_in_shadow");
	return (result);
}

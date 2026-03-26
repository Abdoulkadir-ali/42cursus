/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	check_planes(const t_ray *ray, t_scene *sc, t_hit *hit, bool *any)
{
	t_hit	temp;
	int		i;

	if (!sc)
		return ;
	i = -1;
	while (++i < sc->plane_count)
	{
		if (intersect_plane(ray, &sc->planes[i], &temp))
		{
			if (temp.t < hit->t)
			{
				*hit = temp;
				hit->ref.type = TYPE_PLANE;
				hit->ref.index = i;
				*any = true;
			}
		}
	}
}

t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene)
{
	t_hit	hit;
	bool	any;

	hit.t = TRACE_MAX_DIST;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
	any = bvh_intersect(bvh, ray, &hit);
	if (!any)
		hit.t = TRACE_MAX_DIST;
	check_planes(ray, scene, &hit, &any);
	if (any)
		return (compute_color(&hit, scene, bvh, ray));
	return (vec3(0, 0, 0));
}

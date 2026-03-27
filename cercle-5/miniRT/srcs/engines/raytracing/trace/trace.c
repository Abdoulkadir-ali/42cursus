/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:56:05 by abdoali          ###   ########.fr       */
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

t_vec3	trace_ray(t_rt_engine *rt, const t_ray *ray)
{
	t_hit	hit;
	bool	any;

	hit.t = TRACE_MAX_DIST;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
	any = bvh_intersect(rt->bvh, ray, &hit);
	if (!any)
		hit.t = TRACE_MAX_DIST;
	check_planes(ray, rt->scene, &hit, &any);
	if (any)
		return (compute_color(&hit, rt, ray));
	return (vec3(0, 0, 0));
}

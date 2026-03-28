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

t_vec3	trace_ray(t_rt_engine *rt, const t_ray *ray)
{
	t_hit	hit;

	hit.t = TRACE_MAX_DIST;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
	if (bvh_intersect(rt->bvh, ray, &hit))
		return (compute_color(&hit, rt, ray));
	return (vec3(0, 0, 0));
}

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

	DBG_ENTER("trace_ray");
	hit.t = TRACE_MAX_DIST;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
	if (bvh_intersect(rt->bvh, ray, &hit))
	{
		DBG_INFO_MSG(DBG_CH_RENDER,
			"trace_ray: HIT type=%d idx=%d t=%.4f\n",
			hit.ref.type, hit.ref.index, hit.t);
		DBG_LEAVE("trace_ray");
		return (compute_color(&hit, rt, ray));
	}
	DBG_TRACE_MSG(DBG_CH_RENDER, "trace_ray: MISS\n");
	DBG_LEAVE("trace_ray");
	return (vec3(0, 0, 0));
}

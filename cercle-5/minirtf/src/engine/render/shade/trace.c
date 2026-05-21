/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 16:41:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <math.h>

float	fresnel(float cos_t, float ior)
{
	float	r0;
	float	x;

	r0 = (1.0f - ior) / (1.0f + ior);
	r0 = r0 * r0;
	x = 1.0f - cos_t;
	return (r0 + (1.0f - r0) * x * x * x * x * x);
}

static t_vec3	trace_ray_internal(const t_app *app, const t_ray *r, int depth)
{
	t_hit	h;
	int	hit;

	if (depth >= app->set.rt.max_bounces)
		return (v3(0, 0, 0));
	h.t = T_MAX;
	hit = bvh_traverse(&app->bvh, r, &h, app->scene.bvh_objs);
	hit |= hit_planes(app->scene.planes, app->scene.n_planes, r, &h);
	if (!hit)
		return (sky_color(r->d));
	return (shade(app, r, &h, depth));
}


t_vec3	trace_ray(const t_app *app, const t_ray *r, int depth)
{
	return (trace_ray_internal(app, r, depth));
}

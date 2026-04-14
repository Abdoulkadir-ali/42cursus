/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 14:20:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	shade_trace(const t_bvh *bvh, const t_ray *ray, t_scene *sc,
					t_hit *hit)
{
	t_vec3	p;

	p = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	if (point_inside_eh(p, sc))
		return (vec3(0, 0, 0));
	return (vec3_add(compute_color(hit, sc, bvh, ray),
			add_volumetrics(ray, sc, hit->t)));
}

static t_vec3	do_trace(const t_bvh *bvh, const t_ray *ray,
		t_scene *sc, float *out_t)
{
	t_hit	hit;
	bool	hit_any;
	t_ray	bent;
	bool	cap;

	if (lens_ray(ray, sc, &bent, &cap))
	{
		if (cap)
		{
			if (out_t)
				*out_t = 0.0f;
			return (vec3(0, 0, 0));
		}
		ray = &bent;
	}
	hit.t = 1e30;
	hit_any = bvh_intersect(bvh, ray, &hit);
	check_planes(ray, sc, &hit, &hit_any);
	if (out_t)
		*out_t = (float)hit.t;
	if (hit_any)
		return (shade_trace(bvh, ray, sc, &hit));
	return (add_volumetrics(ray, sc, 1e10));
}

t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *sc)
{
	return (do_trace(bvh, ray, sc, NULL));
}

t_vec3	trace_ray_ex(const t_bvh *bvh, const t_ray *ray, t_scene *sc,
		float *out_t)
{
	return (do_trace(bvh, ray, sc, out_t));
}

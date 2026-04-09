/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/07 21:57:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "raytracing.h"

static void	check_planes(const t_ray *ray, t_scene *sc, t_hit *hit, bool *any)
{
	t_hit	temp;
	size_t	i;

	if (!sc)
		return ;
	i = 0;
	while (i < sc->plane_count)
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
		i++;
	}
}

static t_vec3	add_volumetrics(const t_ray *ray, t_scene *sc, double max_t)
{
	t_vec3	glow;
	size_t	i;
	double	t;
	double	d2;
	t_vec3	lv;
	double	br;

	glow = vec3(0, 0, 0);
	if (!sc || ray->depth > 0)
		return (glow);
	i = 0;
	while (i < sc->light_count)
	{
		lv = vec3_sub(sc->lights[i].transform.pos, ray->origin);
		t = vec3_dot(lv, ray->direction);
		if (t > 0 && t < max_t)
		{
			d2 = vec3_mag_sq(lv) - t * t;
			br = sc->lights[i].brightness;
			glow = vec3_add(glow, vec3_scale(sc->lights[i].rgb,
						br * 0.00004 / (d2 + 0.1)));
		}
		i++;
	}
	return (glow);
}

static t_vec3	do_trace(const t_bvh *bvh, const t_ray *ray,
		t_scene *sc, float *out_t)
{
	t_hit	hit;
	bool	hit_any;

	hit = (t_hit){0};
	hit.t = 1e30;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = 0;
	hit_any = bvh_intersect(bvh, ray, &hit);
	if (!hit_any)
		hit.t = 1e30;
	check_planes(ray, sc, &hit, &hit_any);
	if (out_t)
		*out_t = (float)hit.t;
	if (hit_any)
		return (vec3_add(compute_color(&hit, sc, bvh, ray),
				add_volumetrics(ray, sc, hit.t)));
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

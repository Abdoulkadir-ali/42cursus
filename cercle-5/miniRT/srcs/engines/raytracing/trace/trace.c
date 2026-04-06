/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 21:24:06 by abdoali          ###   ########.fr       */
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
				hit->ref.index = init_index(i, false);
				*any = true;
			}
		}
		i++;
	}
}

static t_vec3	do_trace(const t_bvh *bvh, const t_ray *ray,
		t_scene *sc, float *out_t)
{
	t_hit	hit;
	bool	hit_any;

	hit.t = 1e30;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = init_index(0, true);
	hit_any = bvh_intersect(bvh, ray, &hit);
	if (!hit_any)
		hit.t = 1e30;
	check_planes(ray, sc, &hit, &hit_any);
	if (out_t)
		*out_t = (float)hit.t;
	if (hit_any)
		return (compute_color(&hit, sc, bvh, ray));
	return (vec3(0, 0, 0));
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

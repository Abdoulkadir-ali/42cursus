/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 10:28:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static inline double	safe_rcp(double d)
{
	double	ad;

	ad = __builtin_fabs(d);
	if (__builtin_expect(ad < 1e-20, 0))
		d = __builtin_copysign(1e-20, d);
	return (1.0 / d);
}

static inline void	ray_compute_inv(t_ray *ray)
{
	ray->inv_dir = vec3(safe_rcp(ray->direction.x),
			safe_rcp(ray->direction.y), safe_rcp(ray->direction.z));
	ray->sign[0] = (ray->inv_dir.x < 0);
	ray->sign[1] = (ray->inv_dir.y < 0);
	ray->sign[2] = (ray->inv_dir.z < 0);
}

void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
	ray->depth = 0;
	ray->weight = 1.0;
	ray_compute_inv(ray);
}

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

static t_vec3	do_trace(const t_bvh *bvh, const t_ray *ray,
		t_scene *sc, float *out_t)
{
	t_hit	hit;
	bool	hit_any;

	hit.t = 1e30;
	hit.ref.type = TYPE_NONE;
	hit.ref.index = -1;
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

t_vec3	trace_ray_ex(const t_bvh *bvh, const t_ray *ray, t_scene *sc, float *out_t)
{
	return (do_trace(bvh, ray, sc, out_t));
}

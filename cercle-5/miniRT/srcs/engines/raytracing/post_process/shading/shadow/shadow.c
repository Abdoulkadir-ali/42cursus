/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static inline __attribute__((always_inline))
void	shadow_ray_init(t_ray *ray, t_vec3 origin, t_vec3 dir)
{
	ray->origin = origin;
	ray->direction = dir;
	ray->inv_dir.x = 1.0 / dir.x;
	ray->inv_dir.y = 1.0 / dir.y;
	ray->inv_dir.z = 1.0 / dir.z;
}

__attribute__((optimize("O3")))
static bool	planes_occlude(const t_ray *ray, t_scene *sc, double max_t)
{
	double		denom;
	double		t;
	size_t		i;

	i = 0;
	while (i < sc->plane_count)
	{
		denom = vec3_dot(sc->planes[i].transform.forward, ray->direction);
		if (__builtin_fabs(denom) >= 1e-6)
		{
			t = vec3_dot(vec3_sub(sc->planes[i].transform.pos,
						ray->origin),
					sc->planes[i].transform.forward) / denom;
			if (t > EPSILON && t < max_t)
				return (true);
		}
		i++;
	}
	return (false);
}

__attribute__((optimize("O3")))
bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist)
{
	t_ray	sray;
	t_scene	*sc;

	shadow_ray_init(&sray, p, ldir_norm);
	if (bvh_occluded4(bvh, &sray, dist))
		return (true);
	sc = bvh ? bvh->scene : NULL;
	return (sc && sc->plane_count > 0
		&& planes_occlude(&sray, sc, dist));
}

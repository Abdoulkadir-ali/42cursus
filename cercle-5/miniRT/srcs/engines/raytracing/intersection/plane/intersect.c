/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Intersects a ray with a plane.
*/
__attribute__((optimize("O3")))
bool	intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit)
{
	double	denom;

	denom = vec3_dot(pl->transform.forward, ray->direction);
	if (fabs(denom) < 1e-6)
		return (false);
	hit->t = vec3_dot(vec3_sub(pl->transform.pos, ray->origin),
			pl->transform.forward) / denom;
	if (hit->t < EPSILON)
		return (false);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = pl->transform.forward;
	hit->back_face = false;
	if (vec3_dot(ray->direction, hit->normal) > 0)
	{
		hit->normal = vec3_scale(hit->normal, -1.0);
		hit->back_face = true;
	}
	if (pl->needs_uv)
	{
		get_plane_uv(hit->point, pl->transform.forward, hit);
		denom = fmax(1e-6, pl->transform.scale.x);
		hit->u /= denom;
		hit->v /= denom;
	}
	return (true);
}

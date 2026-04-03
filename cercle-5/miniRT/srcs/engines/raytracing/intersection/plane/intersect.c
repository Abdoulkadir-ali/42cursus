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
bool	intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit)
{
	double	denom;
	double	t;
	double	uv_s;

	denom = vec3_dot(pl->transform.forward, ray->direction);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(pl->transform.pos, ray->origin),
			pl->transform.forward) / denom;
	if (t < EPSILON)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = pl->transform.forward;
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	get_plane_uv(hit->point, pl->transform.forward, hit);
	uv_s = pl->transform.scale.x;
	if (uv_s <= 1e-6)
		uv_s = 1.0;
	hit->u /= uv_s;
	hit->v /= uv_s;
	return (true);
}

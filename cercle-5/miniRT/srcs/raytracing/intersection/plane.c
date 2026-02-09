/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Calculates UV coordinates and tangent space for a plane.
*/
static void	get_plane_uv(t_vec3 p, t_vec3 n, t_hit *hit)
{
	t_vec3	u_axis;
	t_vec3	v_axis;

	if (fabs(n.y) > 0.9)
		u_axis = vec3(1, 0, 0);
	else
		u_axis = vec3(0, 1, 0);
	v_axis = vec3_norm(vec3_cross(n, u_axis));
	u_axis = vec3_norm(vec3_cross(v_axis, n));
	hit->u = vec3_dot(p, u_axis) * 0.1;
	hit->v = vec3_dot(p, v_axis) * 0.1;
	hit->tangent = u_axis;
	hit->bitangent = v_axis;
}

/*
** Intersects a ray with a plane.
*/
bool	intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit)
{
	double	denom;
	double	t;

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
	return (true);
}

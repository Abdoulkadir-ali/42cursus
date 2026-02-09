/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:10:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Calculates UV coordinates for a sphere at a given normal.
*/
static void	get_sphere_uv(t_vec3 normal, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(-normal.y);
	phi = atan2(-normal.z, normal.x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = theta / M_PI;
}

/*
** Sets hit point, normal, UVs and tangent space for a sphere hit.
*/
static void	set_sphere_hit_data(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vec3	up;

	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = vec3_scale(vec3_sub(hit->point, sp->transform.pos),
			1.0 / sqrt(sp->radius_sq));
	get_sphere_uv(hit->normal, &hit->u, &hit->v);
	up = vec3(0, 1, 0);
	if (fabs(vec3_dot(hit->normal, up)) > 0.99)
		up = vec3(0, 0, 1);
	hit->tangent = vec3_norm(vec3_cross(up, hit->normal));
	hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
}

/*
** Intersects a ray with a sphere.
** Uses quadratic formula to find the closest positive hit point.
*/
bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vec3	oc;
	double	cf[3];
	double	t[2];

	oc = vec3_sub(ray->origin, sp->transform.pos);
	cf[0] = vec3_dot(ray->direction, ray->direction);
	cf[1] = 2.0 * vec3_dot(oc, ray->direction);
	cf[2] = vec3_dot(oc, oc) - sp->radius_sq;
	if (!solve_quadratic(cf[0], cf[1], cf[2], &t[0], &t[1]))
		return (false);
	hit->t = (t[0] > EPSILON) ? t[0] : t[1];
	if (hit->t < EPSILON)
		return (false);
	set_sphere_hit_data(ray, sp, hit);
	return (true);
}

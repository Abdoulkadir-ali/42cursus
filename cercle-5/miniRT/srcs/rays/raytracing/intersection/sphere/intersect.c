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
** Sets up the quadratic equation for sphere intersection.
*/
static t_quadratic	setup_sphere_quadratic(const t_ray *ray, t_sphere *sp)
{
	t_vec3		oc;
	double		cf[3];
	t_quadratic	q;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	cf[0] = vec3_dot(ray->direction, ray->direction);
	cf[1] = 2.0 * vec3_dot(oc, ray->direction);
	cf[2] = vec3_dot(oc, oc) - sp->radius_sq;
	q.a = cf[0];
	q.b = cf[1];
	q.c = cf[2];
	return (q);
}

/*
** Selects the valid intersection distance for sphere.
*/
static bool	select_sphere_t(t_quadratic_roots roots, double *t)
{
	if (roots.t1 > EPSILON)
		*t = roots.t1;
	else
		*t = roots.t2;
	return (*t > EPSILON);
}

/*
** Intersects a ray with a sphere.
** Uses quadratic formula to find the closest positive hit point.
*/
bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;

	q = setup_sphere_quadratic(ray, sp);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_sphere_t(roots, &hit->t))
		return (false);
	set_sphere_hit_data(ray, sp, hit);
	return (true);
}

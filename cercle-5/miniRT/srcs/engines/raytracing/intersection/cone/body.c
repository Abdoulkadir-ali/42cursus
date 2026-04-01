/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Sets up the quadratic equation for cone body intersection.
*/
static t_quadratic	setup_cone_quadratic(const t_ray *ray, t_cone *cone)
{
	t_vec3		oc;
	double		cf[3];
	t_quadratic	q;
	double		k;

	k = cone->transform.scale.x / cone->transform.scale.y;
	k = k * k;
	oc = vec3_sub(ray->origin, cone->transform.pos);
	cf[0] = vec3_dot(ray->direction, ray->direction) - k
		* vec3_dot(ray->direction, cone->transform.forward)
		* vec3_dot(ray->direction, cone->transform.forward);
	cf[1] = 2.0 * (vec3_dot(oc, ray->direction) - k * vec3_dot(oc,
				cone->transform.forward) * vec3_dot(ray->direction,
				cone->transform.forward));
	cf[2] = vec3_dot(oc, oc) - k * vec3_dot(oc, cone->transform.forward)
		* vec3_dot(oc, cone->transform.forward);
	q.a = cf[0];
	q.b = cf[1];
	q.c = cf[2];
	return (q);
}

/*
** Checks a single solution for cone body intersection.
*/
static bool	check_cone_t(const t_ray *ray, t_cone *cone, double t, double *tm,
		double y_cutoff)
{
	t_vec3	p;
	double	y;

	if (t > EPSILON && t < *tm)
	{
		p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		y = vec3_dot(vec3_sub(p, cone->transform.pos), cone->transform.forward);
		if (y >= 0 && y <= y_cutoff)
		{
			*tm = t;
			return (true);
		}
	}
	return (false);
}

/*
** Checks intersection with the body of the cone using quadratic formula.
*/
bool	check_cone_body(const t_ray *ray, t_cone *cone, double *t,
		double y_cutoff)
{
	t_quadratic			q;
	t_quadratic_roots	roots;

	q = setup_cone_quadratic(ray, cone);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (check_cone_t(ray, cone, roots.t1, t, y_cutoff))
		return (true);
	return (check_cone_t(ray, cone, roots.t2, t, y_cutoff));
}

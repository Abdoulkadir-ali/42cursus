/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:42:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:42:33 by abdoali          ###   ########.fr       */
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
static bool	check_cone_t(t_ray_query *q, t_cone *cone, double t, double cutoff)
{
	t_vec3	p;
	double	y;

	if (t > EPSILON && t < *(q->tm))
	{
		p = vec3_add(q->ray->origin, vec3_scale(q->ray->direction, t));
		y = vec3_dot(vec3_sub(p, cone->transform.pos), cone->transform.forward);
		if (y >= 0 && y <= cutoff)
		{
			*(q->tm) = t;
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
	t_ray_query			query;

	query.ray = ray;
	query.tm = t;
	query.hit = NULL;
	q = setup_cone_quadratic(ray, cone);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (check_cone_t(&query, cone, roots.t1, y_cutoff))
		return (true);
	return (check_cone_t(&query, cone, roots.t2, y_cutoff));
}

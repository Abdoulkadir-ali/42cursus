/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Sets up the quadratic equation for cylinder body intersection.
*/
static bool	check_body_t(t_ray_query *q, t_cylinder *cy, double t)
{
	t_vec3			p;
	double			h;

	if (t > EPSILON && t < *(q->tm))
	{
		p = vec3_add(q->ray->origin, vec3_scale(q->ray->direction, t));
		h = vec3_dot(vec3_sub(p, cy->transform.pos), cy->transform.forward);
		if (h >= 0 && h <= cy->transform.scale.y)
		{
			*(q->tm) = t;
			q->hit->t = t;
			q->hit->point = p;
			q->hit->normal = vec3_norm(vec3_sub(vec3_sub(p,
							cy->transform.pos),
						vec3_scale(cy->transform.forward, h)));
			q->hit->back_face = false;
			if (vec3_dot(q->ray->direction, q->hit->normal) > 0)
			{
				q->hit->normal = vec3_scale(q->hit->normal, -1.0);
				q->hit->back_face = true;
			}
			get_cylinder_uv((t_entry_point){p, cy->transform.pos,
				cy->transform.scale.x, cy->transform.scale.y, h},
				cy, q->hit, false);
			return (true);
		}
	}
	return (false);
}

static t_quadratic	setup_cylinder_quadratic(const t_ray *ray, t_cylinder *cy)
{
	t_quadratic	q;
	t_vec3		oc;
	double		dd;

	oc = vec3_sub(ray->origin, cy->transform.pos);
	dd = vec3_dot(ray->direction, cy->transform.forward);
	q.a = vec3_dot(ray->direction, ray->direction) - dd * dd;
	q.b = 2.0 * (vec3_dot(ray->direction, oc) - dd * vec3_dot(oc,
				cy->transform.forward));
	q.c = vec3_dot(oc, oc) - vec3_dot(oc, cy->transform.forward)
		* vec3_dot(oc, cy->transform.forward) - cy->radius_sq;
	return (q);
}

/*
** Checks intersection with the side (body) of the cylinder.
*/
bool	check_body(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;
	t_ray_query			query;

	query.ray = ray;
	query.tm = tm;
	query.hit = hit;
	q = setup_cylinder_quadratic(ray, cy);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (check_body_t(&query, cy, roots.t1))
		return (true);
	return (check_body_t(&query, cy, roots.t2));
}

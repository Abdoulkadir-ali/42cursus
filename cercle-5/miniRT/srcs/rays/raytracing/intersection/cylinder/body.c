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
** Sets up the quadratic equation for cylinder body intersection.
*/
static bool	check_body_t(t_check_params params)
{
	t_vec3			p;
	double			h;
	t_entry_point	pt;

	if (params.t > EPSILON && params.t < *params.tm)
	{
		p = vec3_add(params.ray->origin, vec3_scale(params.ray->direction,
					params.t));
		h = vec3_dot(vec3_sub(p, params.cy->transform.pos),
				params.cy->transform.forward);
		if (h >= 0 && h <= params.cy->transform.scale.y)
		{
			*params.tm = params.t;
			params.hit->t = params.t;
			params.hit->point = p;
			params.hit->normal = vec3_norm(vec3_sub(vec3_sub(p,
							params.cy->transform.pos),
						vec3_scale(params.cy->transform.forward, h)));
			pt = (t_entry_point){p, params.cy->transform.pos,
				params.cy->transform.scale.x, params.cy->transform.scale.y, h};
			get_cylinder_uv(pt, params.cy, params.hit, false);
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
		* vec3_dot(oc, cy->transform.forward) - cy->transform.scale.x
		* cy->transform.scale.x;
	return (q);
}

/*
** Checks intersection with the side (body) of the cylinder.
*/
bool	check_body(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;
	t_check_params		params;

	q = setup_cylinder_quadratic(ray, cy);
	if (!solve_quadratic(q, &roots))
		return (false);
	params.ray = ray;
	params.cy = cy;
	params.tm = tm;
	params.hit = hit;
	params.t = roots.t1;
	if (check_body_t(params))
		return (true);
	params.t = roots.t2;
	return (check_body_t(params));
}

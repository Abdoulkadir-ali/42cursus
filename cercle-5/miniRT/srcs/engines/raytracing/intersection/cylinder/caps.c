/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Fills the hit record for a cylinder cap intersection.
*/
static void	fill_cap_hit(t_cylinder *cy, t_ray_query *q,
		t_vec3 center, double normal_sign)
{
	t_entry_point	pt;

	q->hit->normal = vec3_scale(cy->transform.forward, normal_sign);
	pt = (t_entry_point){q->hit->point, center, cy->transform.scale.x,
		cy->transform.scale.y, 0};
	get_cylinder_uv(pt, cy, q->hit, true);
}

/*
** Checks intersection with a cylinder cap.
*/
static bool	check_cap(t_ray_query *q, t_cylinder *cy,
		t_vec3 center, double normal_sign)
{
	double	t;
	double	denom;

	denom = vec3_dot(q->ray->direction, cy->transform.forward);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(center, q->ray->origin),
			cy->transform.forward) / denom;
	if (t > EPSILON && t < *(q->tm))
	{
		q->hit->point = vec3_add(q->ray->origin,
				vec3_scale(q->ray->direction, t));
		if (vec3_mag_sq(vec3_sub(q->hit->point, center))
			<= cy->radius_sq)
		{
			*(q->tm) = t;
			q->hit->t = t;
			fill_cap_hit(cy, q, center, normal_sign);
			return (true);
		}
	}
	return (false);
}

/*
** Checks intersection with the bottom cap of the cylinder.
*/
bool	check_bottom_cap(const t_ray *ray, t_cylinder *cy, double *tm,
		t_hit *hit)
{
	t_ray_query	q;

	q.ray = ray;
	q.tm = tm;
	q.hit = hit;
	return (check_cap(&q, cy, cy->transform.pos, -1.0));
}

/*
** Checks intersection with the top cap of the cylinder.
*/
bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	t_ray_query	q;

	q.ray = ray;
	q.tm = tm;
	q.hit = hit;
	return (check_cap(&q, cy, cy->top, 1.0));
}

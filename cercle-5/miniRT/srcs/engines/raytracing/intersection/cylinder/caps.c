/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Fills the hit record for a cylinder cap intersection.
*/
static void	fill_cap_hit(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit,
		t_vec3 center, double normal_sign, double t, t_vec3 p)
{
	(void)ray;
	t_entry_point	pt;

	*tm = t;
	hit->t = t;
	hit->point = p;
	hit->normal = vec3_scale(cy->transform.forward,
			normal_sign);
	pt = (t_entry_point){p, center, cy->transform.scale.x,
		cy->transform.scale.y, 0};
	get_cylinder_uv(pt, cy, hit, true);
}

/*
** Checks intersection with a cylinder cap.
*/
static bool	check_cap(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit,
		t_vec3 center, double normal_sign)
{
	double	t;
	t_vec3	p;
	double	denom;

	denom = vec3_dot(ray->direction, cy->transform.forward);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(center, ray->origin),
			cy->transform.forward) / denom;
	if (t > EPSILON && t < *tm)
	{
		p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		if (vec3_mag_sq(vec3_sub(p,
					center)) <= cy->transform.scale.x
			* cy->transform.scale.x)
		{
			fill_cap_hit(ray, cy, tm, hit, center, normal_sign, t, p);
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
	return (check_cap(ray, cy, tm, hit, cy->transform.pos, -1.0));
}

/*
** Checks intersection with the top cap of the cylinder.
*/
bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	t_vec3	top;

	top = vec3_add(cy->transform.pos, vec3_scale(cy->transform.forward,
				cy->transform.scale.y));
	return (check_cap(ray, cy, tm, hit, top, 1.0));
}

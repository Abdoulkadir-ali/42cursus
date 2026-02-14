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
static void	fill_cap_hit(t_cap_params params, double t, t_vec3 p)
{
	t_entry_point	pt;

	*params.tm = t;
	params.hit->t = t;
	params.hit->point = p;
	params.hit->normal = vec3_scale(params.cy->transform.forward,
			params.normal_sign);
	pt = (t_entry_point){p, params.center, params.cy->transform.scale.x,
		params.cy->transform.scale.y, 0};
	get_cylinder_uv(pt, params.cy, params.hit, true);
}

/*
** Checks intersection with a cylinder cap.
*/
static bool	check_cap(t_cap_params params)
{
	double	t;
	t_vec3	p;
	double	denom;

	denom = vec3_dot(params.ray->direction, params.cy->transform.forward);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(params.center, params.ray->origin),
			params.cy->transform.forward) / denom;
	if (t > EPSILON && t < *params.tm)
	{
		p = vec3_add(params.ray->origin, vec3_scale(params.ray->direction, t));
		if (vec3_mag_sq(vec3_sub(p,
					params.center)) <= params.cy->transform.scale.x
			* params.cy->transform.scale.x)
		{
			fill_cap_hit(params, t, p);
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
	return (check_cap((t_cap_params){ray, cy, tm, hit, cy->transform.pos,
			-1.0}));
}

/*
** Checks intersection with the top cap of the cylinder.
*/
bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	t_vec3	top;

	top = vec3_add(cy->transform.pos, vec3_scale(cy->transform.forward,
				cy->transform.scale.y));
	return (check_cap((t_cap_params){ray, cy, tm, hit, top, 1.0}));
}

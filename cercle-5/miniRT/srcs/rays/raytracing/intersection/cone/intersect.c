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
** Fills the hit record with point, normal, UVs and tangent space.
*/
void	fill_hit_record(t_hit *hit, const t_ray *ray, t_cone *cone, double t)
{
	t_vec3	p;
	t_vec3	radial;
	t_vec3	temp;
	double	h;

	hit->t = t;
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->point = p;
	h = vec3_dot(vec3_sub(p, cone->transform.pos), cone->transform.forward);
	temp = vec3_sub(p, cone->transform.pos);
	radial = vec3_sub(temp, vec3_scale(cone->transform.forward, h));
	if (vec3_dot(radial, radial) < EPSILON * EPSILON)
		hit->normal = cone->transform.forward;
	else
		hit->normal = vec3_norm(radial);
	get_cone_uv(hit, cone, radial, h);
}

/*
** Main entry point for ray-cone intersection.
*/
bool	intersect_cone(const t_ray *ray, t_cone *cone, t_hit *hit)
{
	double	t;

	t = DBL_MAX;
	if (check_cone_body(ray, cone, &t, cone->transform.scale.y))
	{
		if (t < hit->t)
		{
			fill_hit_record(hit, ray, cone, t);
			return (true);
		}
	}
	return (false);
}

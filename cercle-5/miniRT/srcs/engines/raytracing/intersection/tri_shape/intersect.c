/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/07 21:57:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_tri_shape(const t_ray *ray, t_tri_shape *tr, t_hit *hit)
{
	double	t;
	t_vec2	uv;

	if (!intersect_triangle_fast(ray, tr->v, &t, &uv))
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = tr->normal;
	if (vec3_dot(ray->direction, hit->normal) > 0)
	{
		hit->normal = vec3_scale(hit->normal, -1.0);
		hit->back_face = true;
	}
	else
		hit->back_face = false;
	hit->u = uv.x;
	hit->v = uv.y;
	return (true);
}

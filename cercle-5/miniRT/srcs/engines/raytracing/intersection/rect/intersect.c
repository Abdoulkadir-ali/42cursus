/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 10:34:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	set_rect_hit(const t_ray *ray, t_rect *rc, t_hit *hit, double t)
{
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = rc->normal;
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
}

bool	intersect_rect(const t_ray *ray, t_rect *rc, t_hit *hit)
{
	t_vec3	v[3];
	double	t[2];
	t_vec2	uv[2];
	bool	hp[2];
	int		id;

	v[0] = rc->v[0];
	v[1] = rc->v[1];
	v[2] = rc->v[2];
	hp[0] = intersect_triangle_fast(ray, v, &t[0], &uv[0]);
	v[1] = rc->v[2];
	v[2] = rc->v[3];
	hp[1] = intersect_triangle_fast(ray, v, &t[1], &uv[1]);
	if (!hp[0] && !hp[1])
		return (false);
	id = 0;
	if (!hp[0] || (hp[1] && t[1] < t[0]))
		id = 1;
	set_rect_hit(ray, rc, hit, t[id]);
	hit->u = uv[id].x;
	hit->v = uv[id].y;
	return (true);
}

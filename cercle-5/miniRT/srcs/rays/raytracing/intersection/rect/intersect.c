/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:48:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	setup_rect_hit(t_hit *hit, const t_ray *ray, t_rect *rc, t_vec2 uv)
{
	t_vec3	n;

	hit->u = uv.x;
	hit->v = uv.y;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	n = rc->normal;
	if (vec3_dot(ray->direction, n) > 0.0)
		n = vec3_scale(n, -1.0);
	hit->normal = n;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}

static void	init_rect_ctx(t_rect_ctx *c, t_rect *rc, const t_ray *ray)
{
	c->v[0][0] = rc->v[0];
	c->v[0][1] = rc->v[1];
	c->v[0][2] = rc->v[2];
	c->v[1][0] = rc->v[0];
	c->v[1][1] = rc->v[2];
	c->v[1][2] = rc->v[3];
	c->h[0] = intersect_triangle_fast(ray, c->v[0], &c->t[0], &c->uv[0]);
	c->h[1] = intersect_triangle_fast(ray, c->v[1], &c->t[1], &c->uv[1]);
}

bool	intersect_rect(const t_ray *ray, t_rect *rc, t_hit *hit)
{
	t_rect_ctx	c;

	init_rect_ctx(&c, rc, ray);
	if (!c.h[0] && !c.h[1])
		return (false);
	if (c.h[0] && (!c.h[1] || c.t[0] <= c.t[1]))
	{
		hit->t = c.t[0];
		setup_rect_hit(hit, ray, rc, c.uv[0]);
	}
	else
	{
		hit->t = c.t[1];
		setup_rect_hit(hit, ray, rc, c.uv[1]);
	}
	return (true);
}

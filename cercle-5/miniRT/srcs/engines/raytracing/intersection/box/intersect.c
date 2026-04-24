/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 10:09:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"


PROF_HOT
static inline void	get_calc(t_box *bx, const t_ray *ray, t_box_calc *c)
{
	t_vec3	oc;

	c->ax[0] = bx->ax[0];
	c->ax[1] = bx->ax[1];
	c->ax[2] = bx->ax[2];
	oc = vec3_sub(ray->origin, bx->transform.pos);
	c->p[0] = vec3_dot(oc, c->ax[0]);
	c->p[1] = vec3_dot(oc, c->ax[1]);
	c->p[2] = vec3_dot(oc, c->ax[2]);
	c->d[0] = vec3_dot(ray->direction, c->ax[0]);
	c->d[1] = vec3_dot(ray->direction, c->ax[1]);
	c->d[2] = vec3_dot(ray->direction, c->ax[2]);
	c->h[0] = bx->half_extents.x;
	c->h[1] = bx->half_extents.y;
	c->h[2] = bx->half_extents.z;
	c->inv_d[0] = 1.0 / c->d[0];
	c->inv_d[1] = 1.0 / c->d[1];
	c->inv_d[2] = 1.0 / c->d[2];
	c->ray = *ray;
}

PROF_HOT
static inline bool	test_axis(t_box_calc *c, int i, double *mm, int *eface)
{
	double	t[2];
	double	tmp;

	if (__builtin_fabs(c->d[i]) < 1e-8)
		return (c->p[i] >= -c->h[i] && c->p[i] <= c->h[i]);
	t[0] = (-c->h[i] - c->p[i]) * c->inv_d[i];
	t[1] = (c->h[i] - c->p[i]) * c->inv_d[i];
	if (t[0] > t[1])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
	if (t[0] > mm[0])
	{
		mm[0] = t[0];
		*eface = i;
	}
	if (t[1] < mm[1])
		mm[1] = t[1];
	return (mm[0] <= mm[1]);
}

PROF_HOT
static inline void	set_box_uv(t_box_calc *c, double t, int axis, t_hit *hit)
{
	double	lp[3];

	lp[0] = c->p[0] + c->d[0] * t;
	lp[1] = c->p[1] + c->d[1] * t;
	lp[2] = c->p[2] + c->d[2] * t;
	if (axis == 0)
		hit->u = (lp[1] + c->h[1]) / (2.0 * c->h[1]);
	else
		hit->u = (lp[0] + c->h[0]) / (2.0 * c->h[0]);
	if (axis == 2)
		hit->v = (lp[1] + c->h[1]) / (2.0 * c->h[1]);
	else
		hit->v = (lp[2] + c->h[2]) / (2.0 * c->h[2]);
}

PROF_HOT
static inline void	set_face(t_box_calc *c, double t, int face, t_hit *hit)
{
	hit->t = t;
	hit->point = vec3_add(c->ray.origin, vec3_scale(c->ray.direction, t));
	hit->normal = c->ax[face];
	if (c->d[face] > 0.0)
	{
		hit->normal = vec3_scale(c->ax[face], -1.0);
		hit->back_face = true;
	}
	else
		hit->back_face = false;
	set_box_uv(c, t, face, hit);
}

bool	intersect_box(const t_ray *ray, t_box *bx, t_hit *hit)
{
	t_box_calc	c;
	double		mm[2];
	int			eface;

	get_calc(bx, ray, &c);
	mm[0] = -1e30;
	mm[1] = 1e30;
	eface = 0;
	if (!test_axis(&c, 0, mm, &eface))
		return (false);
	if (!test_axis(&c, 1, mm, &eface))
		return (false);
	if (!test_axis(&c, 2, mm, &eface))
		return (false);
	if (mm[0] >= 1e-6)
	{
		set_face(&c, mm[0], eface, hit);
		return (true);
	}
	return (false);
}

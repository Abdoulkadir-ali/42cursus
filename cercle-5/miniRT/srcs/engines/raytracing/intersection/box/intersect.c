/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:53:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	get_calc(t_box *bx, const t_ray *ray, t_box_calc *c)
{
	t_vec3	oc;

	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		c->ax[0] = vec3(1, 0, 0);
	else
		c->ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(c->ax[0], &c->ax[1], &c->ax[2]);
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
}

static bool	test_axis(t_box_calc *c, int i, double *mm, int *eface, int *xface)
{
	double	t[2];
	double	tmp;

	if (fabs(c->d[i]) < 1e-8)
		return (c->p[i] >= -c->h[i] && c->p[i] <= c->h[i]);
	t[0] = (-c->h[i] - c->p[i]) / c->d[i];
	t[1] = (c->h[i] - c->p[i]) / c->d[i];
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
	{
		mm[1] = t[1];
		*xface = i;
	}
	return (mm[0] <= mm[1]);
}

static void	set_box_uv(t_box_calc *c, double t, int axis, t_hit *hit)
{
	double	lp[3];
	int		u_ax;
	int		v_ax;

	lp[0] = c->p[0] + c->d[0] * t;
	lp[1] = c->p[1] + c->d[1] * t;
	lp[2] = c->p[2] + c->d[2] * t;
	u_ax = (axis == 0) ? 1 : 0;
	v_ax = (axis == 2) ? 1 : 2;
	hit->u = (lp[u_ax] + c->h[u_ax]) / (2.0 * c->h[u_ax]);
	hit->v = (lp[v_ax] + c->h[v_ax]) / (2.0 * c->h[v_ax]);
}

static void	set_face(t_box_calc *c, double t, int face,
				t_hit *hit, const t_ray *ray)
{
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
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
	int			xface;
	size_t		i;

	get_calc(bx, ray, &c);
	mm[0] = -1e30;
	mm[1] = 1e30;
	eface = 0;
	xface = 0;
	i = 0;
	while (i < 3)
		if (!test_axis(&c, i++, mm, &eface, &xface))
			return (false);
	if (mm[0] >= 1e-6)
	{
		set_face(&c, mm[0], eface, hit, ray);
		return (true);
	}
	if (mm[1] >= 1e-6)
	{
		set_face(&c, mm[1], xface, hit, ray);
		return (true);
	}
	return (false);
}

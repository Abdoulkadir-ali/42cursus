/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 07:24:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 17:29:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	check_cap_sph(const t_ray *r, t_capsule *cp, t_cap_ctx *c, bool top)
{
	t_vec3	oc;
	double	d[3];
	double	t;

	if (top)
		oc = vec3_sub(r->origin, c->p1);
	else
		oc = vec3_sub(r->origin, c->p0);
	d[1] = vec3_dot(oc, r->direction);
	d[2] = d[1] * d[1] - (vec3_dot(oc, oc) - cp->radius * cp->radius);
	if (d[2] >= 0.0)
	{
		t = -d[1] - sqrt(d[2]);
		if (t < 1e-6)
			t = -d[1] + sqrt(d[2]);
		if (t >= 1e-6)
		{
			if (top)
				c->t_s1 = t;
			else
				c->t_s0 = t;
		}
	}
}

static void	check_cap_cyl(const t_ray *r, t_capsule *cap, t_cap_ctx *c)
{
	t_vec3	v[2];
	double	d[3];
	double	t;
	double	al;

	v[0] = vec3_sub(r->origin, cap->transform.pos);
	v[1] = vec3_sub(r->direction, vec3_scale(cap->axis,
				vec3_dot(r->direction, cap->axis)));
	d[0] = vec3_dot(v[1], v[1]);
	if (d[0] < 1e-10)
		return ;
	v[0] = vec3_sub(v[0], vec3_scale(cap->axis,
				vec3_dot(v[0], cap->axis)));
	d[1] = 2.0 * vec3_dot(v[1], v[0]);
	d[2] = d[1] * d[1] - 4.0 * d[0] * (vec3_dot(v[0], v[0])
			- cap->radius * cap->radius);
	if (d[2] < 0.0)
		return ;
	t = (-d[1] - sqrt(d[2])) / (2.0 * d[0]);
	if (t < 1e-6)
		t = (-d[1] + sqrt(d[2])) / (2.0 * d[0]);
	if (t < 1e-6)
		return ;
	al = vec3_dot(vec3_sub(vec3_add(r->origin,
					vec3_scale(r->direction, t)), cap->transform.pos),
			cap->axis);
	if (fabs(al) <= cap->half_height)
		c->t_cyl = t;
}

static void	set_cap_norm(t_hit *hit, const t_ray *ray, t_capsule *cap,
		t_cap_ctx *c)
{
	t_vec3	hp;
	t_vec3	n;

	if (c->b_type == 0)
	{
		hp = vec3_sub(hit->point, cap->transform.pos);
		n = vec3_norm(vec3_sub(hp, vec3_scale(cap->axis,
						vec3_dot(hp, cap->axis))));
	}
	else if (c->b_type == 1)
		n = vec3_norm(vec3_sub(hit->point, c->p0));
	else
		n = vec3_norm(vec3_sub(hit->point, c->p1));
	if (vec3_dot(ray->direction, n) > 0.0)
		n = vec3_scale(n, -1.0);
	hit->normal = n;
	hit->u = 0.5;
	hit->v = 0.5;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}

static void	fill_cap_hit(t_hit *hit, const t_ray *ray, t_capsule *cap,
		t_cap_ctx *c)
{
	c->best = c->t_cyl;
	c->b_type = 0;
	if (c->t_s0 < c->best)
	{
		c->best = c->t_s0;
		c->b_type = 1;
	}
	if (c->t_s1 < c->best)
	{
		c->best = c->t_s1;
		c->b_type = 2;
	}
	hit->t = c->best;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, c->best));
	set_cap_norm(hit, ray, cap, c);
}

bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit)
{
	t_cap_ctx	c;

	c.t_cyl = 1e30;
	c.t_s0 = 1e30;
	c.t_s1 = 1e30;
	c.p0 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.p1 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	check_cap_cyl(ray, cap, &c);
	check_cap_sph(ray, cap, &c, false);
	check_cap_sph(ray, cap, &c, true);
	if (c.t_cyl == 1e30 && c.t_s0 == 1e30 && c.t_s1 == 1e30)
		return (false);
	fill_cap_hit(hit, ray, cap, &c);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:49:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	near_sphere_t(const t_ray *ray, t_vec3 center, double radius,
		double *t_out)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	disc;

	oc = vec3_sub(ray->origin, center);
	b = vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	disc = b * b - c;
	if (disc < 0.0)
		return (false);
	*t_out = -b - sqrt(disc);
	if (*t_out < 1e-6)
		*t_out = -b + sqrt(disc);
	return (*t_out > 1e-6);
}

static bool	cylinder_body_t(const t_ray *ray, t_capsule *cap, double *t_out)
{
	t_vec3	oc;
	t_vec3	perp[2];
	double	abc[4];

	oc = vec3_sub(ray->origin, cap->transform.pos);
	perp[0] = vec3_sub(ray->direction,
			vec3_scale(cap->axis, vec3_dot(ray->direction, cap->axis)));
	perp[1] = vec3_sub(oc, vec3_scale(cap->axis, vec3_dot(oc, cap->axis)));
	abc[0] = vec3_dot(perp[0], perp[0]);
	if (abc[0] < 1e-10)
		return (false);
	abc[1] = 2.0 * vec3_dot(perp[0], perp[1]);
	abc[2] = vec3_dot(perp[1], perp[1]) - cap->radius * cap->radius;
	abc[3] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (abc[3] < 0.0)
		return (false);
	*t_out = (-abc[1] - sqrt(abc[3])) / (2.0 * abc[0]);
	if (*t_out < 1e-6)
		*t_out = (-abc[1] + sqrt(abc[3])) / (2.0 * abc[0]);
	abc[3] = vec3_dot(vec3_sub(vec3_add(ray->origin,
					vec3_scale(ray->direction, *t_out)),
				cap->transform.pos), cap->axis);
	return (*t_out > 1e-6 && fabs(abc[3]) <= cap->half_height);
}

static void	update_hit(t_capsule *cp, t_hit *h, t_cap_calc *c, const t_ray *r)
{
	t_vec3	norm;
	t_vec3	ri;
	t_vec3	fw;
	t_vec3	lo;

	if (c->type.i == 0)
		norm = vec3_norm(vec3_sub(vec3_sub(h->point, cp->transform.pos),
					vec3_scale(cp->axis, vec3_dot(vec3_sub(h->point,
								cp->transform.pos), cp->axis))));
	else
		norm = vec3_norm(vec3_sub(h->point, c->p[c->type.i - 1]));
	h->back_face = vec3_dot(r->direction, norm) > 0;
	if (h->back_face)
		norm = vec3_scale(norm, -1.0);
	h->normal = norm;
	vec3_orthonormal_basis(cp->axis, &ri, &fw);
	lo = vec3_sub(h->point, cp->transform.pos);
	if (c->type.i != 0)
		lo = vec3_norm(vec3_sub(h->point, c->p[c->type.i - 1]));
	h->u = (atan2(vec3_dot(lo, fw), vec3_dot(lo, ri)) + M_PI) / (2.0 * M_PI);
	h->v = (vec3_dot(lo, cp->axis) / cp->half_height + 1.0) * 0.5;
	if (c->type.i != 0)
		h->v = (vec3_dot(lo, cp->axis) + 1.0) * 0.5;
	h->tangent = vec3_norm(vec3_cross(cp->axis, h->normal));
	h->bitangent = cp->axis;
	if (c->type.i != 0)
		h->bitangent = vec3_norm(vec3_cross(h->normal, h->tangent));
}

bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit)
{
	t_cap_calc	c;
	int			i;

	c.p[0] = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.p[1] = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.hit[0] = cylinder_body_t(ray, cap, &c.t[0]);
	c.hit[1] = near_sphere_t(ray, c.p[0], cap->radius, &c.t[1]);
	c.hit[2] = near_sphere_t(ray, c.p[1], cap->radius, &c.t[2]);
	c.best = 1e30;
	c.type = init_index(0, true);
	i = -1;
	while (++i < 3)
	{
		if (c.hit[i] && c.t[i] < c.best)
		{
			c.best = c.t[i];
			c.type = init_index(i, false);
		}
	}
	if (c.type.error)
		return (false);
	hit->t = c.best;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, c.best));
	update_hit(cap, hit, &c, ray);
	return (true);
}

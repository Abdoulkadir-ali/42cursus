/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:55:40 by abdoali          ###   ########.fr       */
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
	double	abc[3];
	double	disc;
	double	along;

	oc = vec3_sub(ray->origin, cap->transform.pos);
	perp[0] = vec3_sub(ray->direction,
			vec3_scale(cap->axis, vec3_dot(ray->direction, cap->axis)));
	perp[1] = vec3_sub(oc, vec3_scale(cap->axis, vec3_dot(oc, cap->axis)));
	abc[0] = vec3_dot(perp[0], perp[0]);
	if (abc[0] < 1e-10)
		return (false);
	abc[1] = 2.0 * vec3_dot(perp[0], perp[1]);
	abc[2] = vec3_dot(perp[1], perp[1]) - cap->radius * cap->radius;
	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (disc < 0.0)
		return (false);
	*t_out = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (*t_out < 1e-6)
		*t_out = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	along = vec3_dot(vec3_sub(vec3_add(ray->origin,
					vec3_scale(ray->direction, *t_out)),
				cap->transform.pos), cap->axis);
	return (*t_out > 1e-6 && fabs(along) <= cap->half_height);
}

static void	set_n(const t_ray *ray, t_capsule *cap, t_hit *hit, t_cap_calc *c)
{
	t_vec3	hp;
	t_vec3	norm;

	if (c->type.i == 0)
	{
		hp = vec3_sub(hit->point, cap->transform.pos);
		norm = vec3_norm(vec3_sub(hp,
					vec3_scale(cap->axis, vec3_dot(hp, cap->axis))));
	}
	else
		norm = vec3_norm(vec3_sub(hit->point, c->p[c->type.i - 1]));
	if (vec3_dot(ray->direction, norm) > 0.0)
	{
		norm = vec3_scale(norm, -1.0);
		hit->back_face = true;
	}
	else
		hit->back_face = false;
	hit->normal = norm;
}

static void	get_best(t_cap_calc *c)
{
	int	i;

	c->best = 1e30;
	c->type = init_index(0, true);
	i = 0;
	while (i < 3)
	{
		if (c->hit[i] && c->t[i] < c->best)
		{
			c->best = c->t[i];
			c->type = init_index(i, false);
		}
		i++;
	}
}

static void	set_capsule_uv(t_capsule *cap, t_hit *hit, t_cap_calc *c)
{
	t_vec3	up;
	t_vec3	right;
	t_vec3	fwd;
	t_vec3	local;
	double	along;

	vec3_orthonormal_basis(cap->axis, &right, &fwd);
	if (c->type.i == 0)
	{
		local = vec3_sub(hit->point, cap->transform.pos);
		along = vec3_dot(local, cap->axis);
		hit->u = (atan2(vec3_dot(local, fwd), vec3_dot(local, right))
				+ M_PI) / (2.0 * M_PI);
		hit->v = (along / cap->half_height + 1.0) * 0.5;
		hit->tangent = vec3_norm(vec3_cross(cap->axis, hit->normal));
		hit->bitangent = cap->axis;
	}
	else
	{
		up = cap->axis;
		local = vec3_norm(vec3_sub(hit->point, c->p[c->type.i - 1]));
		hit->u = (atan2(vec3_dot(local, fwd), vec3_dot(local, right))
				+ M_PI) / (2.0 * M_PI);
		hit->v = (vec3_dot(local, up) + 1.0) * 0.5;
		hit->tangent = vec3_norm(vec3_cross(up, hit->normal));
		hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
	}
}

bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit)
{
	t_cap_calc	c;

	c.p[0] = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.p[1] = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	c.hit[0] = cylinder_body_t(ray, cap, &c.t[0]);
	c.hit[1] = near_sphere_t(ray, c.p[0], cap->radius, &c.t[1]);
	c.hit[2] = near_sphere_t(ray, c.p[1], cap->radius, &c.t[2]);
	get_best(&c);
	if (c.type.error)
		return (false);
	hit->t = c.best;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, c.best));
	set_n(ray, cap, hit, &c);
	set_capsule_uv(cap, hit, &c);
	return (true);
}

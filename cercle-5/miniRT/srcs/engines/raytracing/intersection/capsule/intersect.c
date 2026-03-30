/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 07:24:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 07:30:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "objects.h"
#include <math.h>

/*
** Returns closest positive t for a sphere at `center` with `radius`.
** Returns false if no valid hit (discriminant < 0 or both roots <= epsilon).
*/
static bool	near_sphere_t(const t_ray *ray, t_vec3 center, double radius,
		double *t_out)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	disc;
	double	t;

	oc = vec3_sub(ray->origin, center);
	b = vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	disc = b * b - c;
	if (disc < 0.0)
		return (false);
	t = -b - sqrt(disc);
	if (t < 1e-6)
		t = -b + sqrt(disc);
	if (t < 1e-6)
		return (false);
	*t_out = t;
	return (true);
}

/*
** Tests the ray against the finite cylinder body of the capsule.
** Stores the hit t and the along-axis projection in *along_out.
*/
static bool	cylinder_body_t(const t_ray *ray, t_capsule *cap,
		double *t_out, double *along_out)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t;
	double	along;

	oc = vec3_sub(ray->origin, cap->transform.pos);
	d_perp = vec3_sub(ray->direction,
			vec3_scale(cap->axis, vec3_dot(ray->direction, cap->axis)));
	oc_perp = vec3_sub(oc,
			vec3_scale(cap->axis, vec3_dot(oc, cap->axis)));
	a = vec3_dot(d_perp, d_perp);
	if (a < 1e-10)
		return (false);
	b = 2.0 * vec3_dot(d_perp, oc_perp);
	c = vec3_dot(oc_perp, oc_perp) - cap->radius * cap->radius;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (false);
	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t < 1e-6)
		t = (-b + sqrt(disc)) / (2.0 * a);
	if (t < 1e-6)
		return (false);
	along = vec3_dot(vec3_sub(
				vec3_add(ray->origin, vec3_scale(ray->direction, t)),
				cap->transform.pos), cap->axis);
	if (fabs(along) > cap->half_height)
		return (false);
	*t_out = t;
	*along_out = along;
	return (true);
}

bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit)
{
	t_vec3	p0;
	t_vec3	p1;
	double	t_cyl;
	double	along;
	double	t_s0;
	double	t_s1;
	bool	h_cyl;
	bool	h_s0;
	bool	h_s1;
	double	best;
	int		best_type;
	t_vec3	hp;
	t_vec3	n;

	t_cyl = 1e30;
	t_s0 = 1e30;
	t_s1 = 1e30;
	along = 0.0;

	p0 = vec3_sub(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	p1 = vec3_add(cap->transform.pos,
			vec3_scale(cap->axis, cap->half_height));
	h_cyl = cylinder_body_t(ray, cap, &t_cyl, &along);
	h_s0 = near_sphere_t(ray, p0, cap->radius, &t_s0);
	h_s1 = near_sphere_t(ray, p1, cap->radius, &t_s1);
	if (!h_cyl && !h_s0 && !h_s1)
		return (false);
	best = 1e30;
	best_type = -1;
	if (h_cyl && t_cyl < best)
	{
		best = t_cyl;
		best_type = 0;
	}
	if (h_s0 && t_s0 < best)
	{
		best = t_s0;
		best_type = 1;
	}
	if (h_s1 && t_s1 < best)
	{
		best = t_s1;
		best_type = 2;
	}
	hit->t = best;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, best));
	if (best_type == 0)
	{
		hp = vec3_sub(hit->point, cap->transform.pos);
		n = vec3_norm(vec3_sub(hp,
					vec3_scale(cap->axis, vec3_dot(hp, cap->axis))));
	}
	else if (best_type == 1)
		n = vec3_norm(vec3_sub(hit->point, p0));
	else
		n = vec3_norm(vec3_sub(hit->point, p1));
	if (vec3_dot(ray->direction, n) > 0.0)
		n = vec3_scale(n, -1.0);
	hit->normal = n;
	hit->u = 0.5;
	hit->v = 0.5;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}

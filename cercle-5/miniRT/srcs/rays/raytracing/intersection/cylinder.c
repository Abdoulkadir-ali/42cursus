/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Calculates UV coordinates and tangent space for a cylinder intersection.
*/
static void	get_cylinder_uv(t_entry_point pt, t_cylinder *cy, t_hit *hit,
		bool cap)
{
	t_vec3	u_ax;
	t_vec3	v_ax;
	double	u_v[2];

	vec3_orthonormal_basis(cy->transform.forward, &u_ax, &v_ax);
	if (cap)
	{
		hit->u = (vec3_dot(vec3_sub(pt.p, pt.center), u_ax) / pt.radius + 1) * 0.5;
		hit->v = (vec3_dot(vec3_sub(pt.p, pt.center), v_ax) / pt.radius + 1) * 0.5;
		hit->tangent = u_ax;
		hit->bitangent = v_ax;
	}
	else
	{
		u_v[0] = vec3_dot(vec3_sub(pt.p, pt.center), u_ax);
		u_v[1] = vec3_dot(vec3_sub(pt.p, pt.center), v_ax);
		hit->u = (atan2(u_v[1], u_v[0]) + M_PI) / (2 * M_PI);
		hit->v = pt.h / pt.height;
		hit->tangent = vec3_norm(vec3_cross(hit->normal, cy->transform.forward));
		hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
	}
}

/*
** Checks intersection with the bottom cap of the cylinder.
*/
static bool	check_bottom_cap(const t_ray *ray, t_cylinder *cy, double *tm,
		t_hit *hit)
{
	double			t;
	t_vec3			p;
	t_entry_point	pt;
	double			denom;

	denom = vec3_dot(ray->direction, cy->transform.forward);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(cy->transform.pos, ray->origin),
			cy->transform.forward) / denom;
	if (t > EPSILON && t < *tm)
	{
		p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		if (vec3_mag_sq(vec3_sub(p, cy->transform.pos))
			<= cy->transform.scale.x * cy->transform.scale.x)
		{
			*tm = t;
			hit->t = t;
			hit->point = p;
			hit->normal = vec3_scale(cy->transform.forward, -1.0);
			pt = (t_entry_point){p, cy->transform.pos, cy->transform.scale.x,
				cy->transform.scale.y, 0};
			return (get_cylinder_uv(pt, cy, hit, true), true);
		}
	}
	return (false);
}

/*
** Checks intersection with the top cap of the cylinder.
*/
static bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm,
		t_hit *hit)
{
	double			t;
	t_vec3			p;
	t_vec3			top;
	t_entry_point	pt;
	double			denom;

	denom = vec3_dot(ray->direction, cy->transform.forward);
	top = vec3_add(cy->transform.pos, vec3_scale(cy->transform.forward,
				cy->transform.scale.y));
	t = vec3_dot(vec3_sub(top, ray->origin), cy->transform.forward) / denom;
	if (t > EPSILON && t < *tm)
	{
		p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		if (vec3_mag_sq(vec3_sub(p, top)) <= cy->transform.scale.x
			* cy->transform.scale.x)
		{
			*tm = t;
			hit->t = t;
			hit->point = p;
			hit->normal = cy->transform.forward;
			pt = (t_entry_point){p, top, cy->transform.scale.x,
				cy->transform.scale.y, 0};
			return (get_cylinder_uv(pt, cy, hit, true), true);
		}
	}
	return (false);
}

/*
** Checks a single solution of the quadratic for cylinder body intersection.
*/
static bool	check_body_t(const t_ray *ray, t_cylinder *cy, double t,
		double *tm, t_hit *hit)
{
	t_vec3			p;
	double			h;
	t_entry_point	pt;

	if (t > EPSILON && t < *tm)
	{
		p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
		h = vec3_dot(vec3_sub(p, cy->transform.pos), cy->transform.forward);
		if (h >= 0 && h <= cy->transform.scale.y)
		{
			*tm = t;
			hit->t = t;
			hit->point = p;
			hit->normal = vec3_norm(vec3_sub(vec3_sub(p, cy->transform.pos),
						vec3_scale(cy->transform.forward, h)));
			pt = (t_entry_point){p, cy->transform.pos, cy->transform.scale.x,
				cy->transform.scale.y, h};
			get_cylinder_uv(pt, cy, hit, false);
			return (true);
		}
	}
	return (false);
}

/*
** Checks intersection with the side (body) of the cylinder.
*/
static bool	check_body(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit)
{
	double	cf[3];
	double	t[2];
	t_vec3	oc;
	double	dd;
	double	od;

	oc = vec3_sub(ray->origin, cy->transform.pos);
	dd = vec3_dot(ray->direction, cy->transform.forward);
	od = vec3_dot(oc, cy->transform.forward);
	cf[0] = vec3_dot(ray->direction, ray->direction) - dd * dd;
	cf[1] = 2.0 * (vec3_dot(ray->direction, oc) - dd * od);
	cf[2] = vec3_dot(oc, oc) - od * od - cy->transform.scale.x
		* cy->transform.scale.x;
	if (!solve_quadratic(cf[0], cf[1], cf[2], &t[0], &t[1]))
		return (false);
	if (check_body_t(ray, cy, t[0], tm, hit))
		return (true);
	return (check_body_t(ray, cy, t[1], tm, hit));
}

/*
** Main entry point for ray-cylinder intersection.
*/
bool	intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	double	t_min;
	bool	hit_found;

	t_min = DBL_MAX;
	hit_found = false;
	if (check_body(ray, cy, &t_min, hit))
		hit_found = true;
	if (check_bottom_cap(ray, cy, &t_min, hit))
		hit_found = true;
	if (check_top_cap(ray, cy, &t_min, hit))
		hit_found = true;
	if (hit_found)
	{
		if (vec3_dot(ray->direction, hit->normal) > 0)
			hit->normal = vec3_scale(hit->normal, -1.0);
	}
	return (hit_found);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 05:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 15:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Calculates UV coordinates and tangent space for a cone.
*/
static void	get_cone_uv(t_hit *hit, t_cone *cone, t_vec3 radial, double h)
{
	t_vec3	u_ax;
	t_vec3	v_ax;
	double	u_v[2];

	vec3_orthonormal_basis(cone->transform.forward, &u_ax, &v_ax);
	u_v[0] = vec3_dot(radial, u_ax);
	u_v[1] = vec3_dot(radial, v_ax);
	hit->u = (atan2(u_v[1], u_v[0]) + M_PI) / (2 * M_PI);
	hit->v = h / cone->transform.scale.y;
	hit->tangent = vec3_norm(vec3_cross(hit->normal, cone->transform.forward));
	hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
}

/*
** Fills the hit record with point, normal, and UV data for a cone intersection.
*/
static void	fill_hit_record(t_hit *hit, const t_ray *ray, t_cone *cone,
		double t)
{
	t_vec3	temp;
	double	scale;
	double	k;
	double	h;
	t_vec3	center_h;

	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	k = cone->transform.scale.x / cone->transform.scale.y;
	temp = vec3_sub(hit->point, cone->transform.pos);
	scale = (1 + k * k) * vec3_dot(temp, cone->transform.forward);
	hit->normal = vec3_norm(vec3_sub(temp,
				vec3_scale(cone->transform.forward, scale)));
	h = vec3_dot(temp, cone->transform.forward);
	center_h = vec3_add(cone->transform.pos,
			vec3_scale(cone->transform.forward, h));
	get_cone_uv(hit, cone, vec3_sub(hit->point, center_h), h);
	if (vec3_dot(hit->normal, ray->direction) > 0)
		hit->normal = vec3_scale(hit->normal, -1);
}

/*
** Solves the quadratic equation for ray-cone intersection.
*/
static bool	check_cone_body(const t_ray *ray, t_cone *cone,
		double *t, double y_cutoff)
{
	t_vec3	oc;
	double	m;
	double	cf[3];
	double	rt[2];
	double	v[2];

	oc = vec3_sub(ray->origin, cone->transform.pos);
	m = (cone->transform.scale.x / cone->transform.scale.y)
		* (cone->transform.scale.x / cone->transform.scale.y);
	v[0] = vec3_dot(ray->direction, cone->transform.forward);
	v[1] = vec3_dot(oc, cone->transform.forward);
	cf[0] = vec3_dot(ray->direction, ray->direction) - (1 + m)
		* v[0] * v[0];
	cf[1] = 2 * (vec3_dot(ray->direction, oc) - (1 + m) * v[0] * v[1]);
	cf[2] = vec3_dot(oc, oc) - (1 + m) * v[1] * v[1];
	if (!solve_quadratic(cf[0], cf[1], cf[2], &rt[0], &rt[1]))
		return (false);
	*t = rt[0];
	if (!(*t > EPSILON && (v[1] + *t * v[0]) >= 0
			&& (v[1] + *t * v[0]) <= y_cutoff))
	{
		*t = rt[1];
		if (!(*t > EPSILON && (v[1] + *t * v[0]) >= 0
				&& (v[1] + *t * v[0]) <= y_cutoff))
			return (false);
	}
	return (true);
}

/*
** Main entry point for ray-cone intersection.
*/
bool	intersect_cone(const t_ray *ray, t_cone *cone, t_hit *hit)
{
	double	t;

	if (check_cone_body(ray, cone, &t, cone->transform.scale.y))
	{
		if (t < hit->t)
		{
			fill_hit_record(hit, ray, cone, t);
			return (true);
		}
	}
	return (false);
}

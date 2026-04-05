/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	select_sphere_t(t_quadratic_roots roots, double *t)
{
	if (roots.t1 > EPSILON)
		*t = roots.t1;
	else
		*t = roots.t2;
	return (*t > EPSILON);
}

static void	scale_normal(t_hit *hit, t_vec3 inv_scale, t_vec3 n_local,
		bool needs_uv)
{
	t_vec3	n_world;

	n_world.x = n_local.x * inv_scale.x;
	n_world.y = n_local.y * inv_scale.y;
	n_world.z = n_local.z * inv_scale.z;
	n_world.w = 0;
	hit->normal = vec3_norm(n_world);
	if (needs_uv)
		get_sphere_uv(n_local, &hit->u, &hit->v);
}

static void	build_local_ray(t_vec3 *lo, t_vec3 *ld, const t_ray *r,
		t_sphere *sp)
{
	t_vec3	is;

	is = sp->inv_scale;
	lo->x = (r->origin.x - sp->transform.pos.x) * is.x;
	lo->y = (r->origin.y - sp->transform.pos.y) * is.y;
	lo->z = (r->origin.z - sp->transform.pos.z) * is.z;
	lo->w = 0.0;
	ld->x = r->direction.x * is.x;
	ld->y = r->direction.y * is.y;
	ld->z = r->direction.z * is.z;
	ld->w = 0.0;
}

static bool	solve_deformed(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vec3				lo;
	t_vec3				ld;
	t_quadratic			q;
	t_quadratic_roots	roots;

	build_local_ray(&lo, &ld, ray, sp);
	q.a = vec3_dot(ld, ld);
	q.b = 2.0 * vec3_dot(lo, ld);
	q.c = vec3_dot(lo, lo) - sp->radius_sq;
	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_sphere_t(roots, &hit->t))
		return (false);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	scale_normal(hit, sp->inv_scale,
		vec3_norm(vec3_add(lo, vec3_scale(ld, hit->t))), sp->needs_uv);
	return (true);
}

bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vec3	oc;
	double	b;
	double	disc;
	double	sq;

	if (sp->is_deformed)
		return (solve_deformed(ray, sp, hit));
	oc = vec3_sub(ray->origin, sp->transform.pos);
	b = vec3_dot(oc, ray->direction);
	disc = b * b - (vec3_dot(oc, oc) - sp->radius_sq);
	if (disc < 0.0)
		return (false);
	sq = sqrt(disc);
	hit->t = -b - sq;
	if (hit->t <= EPSILON)
		hit->t = -b + sq;
	if (hit->t <= EPSILON)
		return (false);
	set_sphere_hit_data(ray, sp, hit);
	return (true);
}

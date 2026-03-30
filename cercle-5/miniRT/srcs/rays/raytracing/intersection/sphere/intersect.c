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

static t_quadratic	setup_sphere_quadratic(const t_ray *ray, t_sphere *sp)
{
	t_vec3		oc;
	t_quadratic	q;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	q.a = vec3_dot(ray->direction, ray->direction);
	q.b = 2.0 * vec3_dot(oc, ray->direction);
	q.c = vec3_dot(oc, oc) - sp->radius_sq;
	return (q);
}

static bool	select_sphere_t(t_quadratic_roots roots, double *t)
{
	if (roots.t1 > EPSILON)
		*t = roots.t1;
	else
		*t = roots.t2;
	return (*t > EPSILON);
}

static void	deformed_normal(t_hit *hit, t_mat4 inv, t_vec3 n_local)
{
	t_vec3	n_world;

	n_world.x = inv.m[0][0] * n_local.x + inv.m[1][0] * n_local.y
		+ inv.m[2][0] * n_local.z;
	n_world.y = inv.m[0][1] * n_local.x + inv.m[1][1] * n_local.y
		+ inv.m[2][1] * n_local.z;
	n_world.z = inv.m[0][2] * n_local.x + inv.m[1][2] * n_local.y
		+ inv.m[2][2] * n_local.z;
	n_world.w = 0;
	hit->normal = vec3_norm(n_world);
	get_sphere_uv(n_local, &hit->u, &hit->v);
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
}

static bool	solve_deformed(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_mat4				inv;
	t_ray				local_ray;
	t_sphere			temp_sp;
	t_quadratic			q;
	t_quadratic_roots	roots;

	inv = sp->inv_transform;
	local_ray.origin = mat4_mul_pos(inv, ray->origin);
	local_ray.direction = mat4_mul_vec3(inv, ray->direction);
	temp_sp = *sp;
	temp_sp.transform.pos = vec3(0, 0, 0);
	q = setup_sphere_quadratic(&local_ray, &temp_sp);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_sphere_t(roots, &hit->t))
		return (false);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	deformed_normal(hit, inv, vec3_norm(vec3_add(local_ray.origin,
				vec3_scale(local_ray.direction, hit->t))));
	return (true);
}

bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;

	if (sp->is_deformed)
		return (solve_deformed(ray, sp, hit));
	q = setup_sphere_quadratic(ray, sp);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_sphere_t(roots, &hit->t))
		return (false);
	set_sphere_hit_data(ray, sp, hit);
	return (true);
}

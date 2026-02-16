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

/*
** Sets up the quadratic equation for sphere intersection.
*/
static t_quadratic	setup_sphere_quadratic(const t_ray *ray, t_sphere *sp)
{
	t_vec3		oc;
	double		cf[3];
	t_quadratic	q;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	cf[0] = vec3_dot(ray->direction, ray->direction);
	cf[1] = 2.0 * vec3_dot(oc, ray->direction);
	cf[2] = vec3_dot(oc, oc) - sp->radius_sq;
	q.a = cf[0];
	q.b = cf[1];
	q.c = cf[2];
	return (q);
}

/*
** Selects the valid intersection distance for sphere.
*/
static bool	select_sphere_t(t_quadratic_roots roots, double *t)
{
	if (roots.t1 > EPSILON)
		*t = roots.t1;
	else
		*t = roots.t2;
	return (*t > EPSILON);
}

/*
** Intersects a ray with a sphere.
** Uses quadratic formula to find the closest positive hit point.
*/
/*
** Intersects a ray with a sphere.
** Uses quadratic formula to find the closest positive hit point.
*/
bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;
	bool				deformed;
	t_ray				local_ray;
	t_mat4				inv;

	deformed = sp->is_deformed;
	if (deformed)
	{
		inv = sp->inv_transform;
		local_ray.origin = mat4_mul_pos(inv, ray->origin);
		local_ray.direction = mat4_mul_vec3(inv, ray->direction);
		/* Intersect with unit sphere at origin */
		t_sphere temp_sp = *sp;
		temp_sp.transform.pos = vec3(0, 0, 0);
		/* Scale-invariant radius in local space is the base sphere radius */
		q = setup_sphere_quadratic(&local_ray, &temp_sp);
	}
	else
		q = setup_sphere_quadratic(ray, sp);

	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_sphere_t(roots, &hit->t))
		return (false);
		
	if (deformed)
	{
		hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
		
		t_vec3 p_local_hit = vec3_add(local_ray.origin, 
				vec3_scale(local_ray.direction, hit->t));
		/* Normal in local space is radial from origin */
		t_vec3 n_local = vec3_norm(p_local_hit);
		
		/* Transform Normal to World: N = Transpose(M_inv) * n_local */
		t_vec3 n_world;
		n_world.x = inv.m[0][0]*n_local.x + inv.m[1][0]*n_local.y + inv.m[2][0]*n_local.z;
		n_world.y = inv.m[0][1]*n_local.x + inv.m[1][1]*n_local.y + inv.m[2][1]*n_local.z;
		n_world.z = inv.m[0][2]*n_local.x + inv.m[1][2]*n_local.y + inv.m[2][2]*n_local.z;
		n_world.w = 0;
		
		hit->normal = vec3_norm(n_world);
		/* UVs are based on the local spherical projection */
		get_sphere_uv(n_local, &hit->u, &hit->v);
		vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	}
	else
		set_sphere_hit_data(ray, sp, hit);
	return (true);
}

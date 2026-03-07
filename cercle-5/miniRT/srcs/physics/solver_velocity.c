/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_velocity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"
#include "scene.h"

static double	get_inv_mass(t_physics_body *body)
{
	if (!body || body->mass <= 1e-6 || body->is_static)
		return (0.0);
	return (1.0 / body->mass);
}

static void	apply_normal_impulse(t_contact *ct, double inv_a, double inv_b,
		double vn)
{
	double	j;
	t_vec3	impulse;

	j = -(1.0 + ct->restitution) * vn / (inv_a + inv_b);
	impulse = vec3_scale(ct->normal, j);
	if (ct->a && inv_a > 0.0)
		ct->a->velocity = vec3_sub(ct->a->velocity,
				vec3_scale(impulse, inv_a));
	if (ct->b && inv_b > 0.0)
		ct->b->velocity = vec3_add(ct->b->velocity,
				vec3_scale(impulse, inv_b));
}

static void	apply_torque(t_physics_body *body, t_vec3 r, t_vec3 f_impulse,
		double inv_m, double sign)
{
	t_vec3	torque;
	double	r2;
	double	inv_inertia;

	torque = vec3_cross(r, vec3_scale(f_impulse, sign));
	r2 = vec3_mag_sq(r);
	inv_inertia = 0.0;
	if (r2 > 1e-6)
		inv_inertia = 2.5 / r2;
	body->angular_velocity = vec3_add(body->angular_velocity,
			vec3_scale(torque, inv_m * inv_inertia));
}

static void	apply_friction(t_contact *ct, double inv_a, double inv_b,
		t_vec3 rel_v)
{
	t_vec3	vt_vec;
	t_vec3	tangent;
	double	jt;
	t_vec3	f_impulse;

	vt_vec = vec3_sub(rel_v, vec3_scale(ct->normal,
				vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt_vec) <= 1e-6)
		return ;
	tangent = vec3_norm(vt_vec);
	jt = -vec3_dot(rel_v, tangent) / (inv_a + inv_b);
	if (jt > 0.0)
		jt = 0.0;
	f_impulse = vec3_scale(tangent, jt * ct->friction);
	if (ct->a && inv_a > 0.0)
	{
		ct->a->velocity = vec3_sub(ct->a->velocity,
				vec3_scale(f_impulse, inv_a));
		apply_torque(ct->a, ct->ra, f_impulse, inv_a, -1.0);
	}
	if (ct->b && inv_b > 0.0)
	{
		ct->b->velocity = vec3_add(ct->b->velocity,
				vec3_scale(f_impulse, inv_b));
		apply_torque(ct->b, ct->rb, f_impulse, inv_b, 1.0);
	}
}

static void	solve_one_velocity(t_contact *ct, double inv_a, double inv_b)
{
	t_vec3	va;
	t_vec3	vb;
	t_vec3	rel_v;
	double	vn;

	va = vec3(0, 0, 0);
	vb = vec3(0, 0, 0);
	if (ct->a)
		va = ct->a->velocity;
	if (ct->b)
		vb = ct->b->velocity;
	rel_v = vec3_sub(vb, va);
	vn = vec3_dot(rel_v, ct->normal);
	if (vn < 0.0)
		apply_normal_impulse(ct, inv_a, inv_b, vn);
	va = vec3(0, 0, 0);
	vb = vec3(0, 0, 0);
	if (ct->a)
		va = vec3_add(ct->a->velocity,
				vec3_cross(ct->a->angular_velocity, ct->ra));
	if (ct->b)
		vb = vec3_add(ct->b->velocity,
				vec3_cross(ct->b->angular_velocity, ct->rb));
	apply_friction(ct, inv_a, inv_b, vec3_sub(vb, va));
}

void	solve_velocities(t_contact *c, int count)
{
	int		i;
	double	inv_a;
	double	inv_b;

	i = 0;
	while (i < count)
	{
		inv_a = get_inv_mass(c[i].a);
		inv_b = get_inv_mass(c[i].b);
		if (inv_a + inv_b > 1e-8)
			solve_one_velocity(&c[i], inv_a, inv_b);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:52:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:52:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static double	get_inv_mass(t_physics_body *body)
{
	if (!body || body->mass <= 1e-6 || body->is_static)
		return (0.0);
	return (1.0 / body->mass);
}

/*
** Angular contribution to the impulse denominator for direction dir at arm r.
** = inv_m * |(r × dir)|² projected through diagonal inv_inertia tensor.
** This prevents the effective angular restitution from exceeding 1.0.
*/
static double	ang_term(t_physics_body *body, t_vec3 r, t_vec3 dir,
		double inv_m)
{
	t_vec3	rxd;

	if (!body || inv_m < 1e-9)
		return (0.0);
	rxd = vec3_cross(r, dir);
	return (inv_m * (rxd.x * rxd.x * body->inv_inertia.x
			+ rxd.y * rxd.y * body->inv_inertia.y
			+ rxd.z * rxd.z * body->inv_inertia.z));
}

/* Velocity of the body at contact arm r (linear + rotational). */
static t_vec3	point_vel(t_physics_body *body, t_vec3 r)
{
	if (!body)
		return (vec3(0, 0, 0));
	return (vec3_add(body->velocity,
			vec3_cross(body->angular_velocity, r)));
}

static void	apply_torque(t_physics_body *body, t_vec3 r, t_vec3 impulse,
		double inv_m, double sign)
{
	t_vec3	torque;
	t_vec3	dw;

	torque = vec3_cross(r, vec3_scale(impulse, sign));
	dw.x = torque.x * inv_m * body->inv_inertia.x;
	dw.y = torque.y * inv_m * body->inv_inertia.y;
	dw.z = torque.z * inv_m * body->inv_inertia.z;
	body->angular_velocity = vec3_add(body->angular_velocity, dw);
}

static void	apply_friction(t_contact *ct, double inv_a, double inv_b,
		t_vec3 rel_v)
{
	t_vec3	vt_vec;
	t_vec3	tangent;
	double	jt;
	double	denom;
	t_vec3	f_impulse;

	vt_vec = vec3_sub(rel_v, vec3_scale(ct->normal,
				vec3_dot(rel_v, ct->normal)));
	if (vec3_mag_sq(vt_vec) <= 1e-6)
		return ;
	tangent = vec3_norm(vt_vec);
	denom = inv_a + inv_b
		+ ang_term(ct->a, ct->ra, tangent, inv_a)
		+ ang_term(ct->b, ct->rb, tangent, inv_b);
	if (denom < 1e-9)
		return ;
	jt = -vec3_dot(rel_v, tangent) / denom;
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
	double	denom;
	double	j;
	double	e;
	t_vec3	impulse;

	/* Use point velocity (linear + omega×r) for correct relative velocity */
	va = point_vel(ct->a, ct->ra);
	vb = point_vel(ct->b, ct->rb);
	rel_v = vec3_sub(vb, va);
	vn = vec3_dot(rel_v, ct->normal);
	if (vn < 0.0)
	{
		denom = inv_a + inv_b
			+ ang_term(ct->a, ct->ra, ct->normal, inv_a)
			+ ang_term(ct->b, ct->rb, ct->normal, inv_b);
		if (denom < 1e-9)
			return ;
		e = 0.0;
		if (vn < -RESTITUTION_SLOP)
			e = ct->restitution;
		j = -(1.0 + e) * vn / denom;
		impulse = vec3_scale(ct->normal, j);
		if (ct->a && inv_a > 0.0)
		{
			ct->a->velocity = vec3_sub(ct->a->velocity,
					vec3_scale(impulse, inv_a));
			apply_torque(ct->a, ct->ra, impulse, inv_a, -1.0);
		}
		if (ct->b && inv_b > 0.0)
		{
			ct->b->velocity = vec3_add(ct->b->velocity,
					vec3_scale(impulse, inv_b));
			apply_torque(ct->b, ct->rb, impulse, inv_b, 1.0);
		}
		va = point_vel(ct->a, ct->ra);
		vb = point_vel(ct->b, ct->rb);
		apply_friction(ct, inv_a, inv_b, vec3_sub(vb, va));
	}
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

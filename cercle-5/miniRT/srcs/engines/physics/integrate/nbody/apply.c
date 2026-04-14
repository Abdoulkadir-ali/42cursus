/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbody_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

#define GRAV_SOFT2	0.25
#define GRAV_ACCEL_CAP	200.0

static void	apply_grav_to_body(t_physics_body *b, t_vec3 dir, double f)
{
	double	fa;

	fa = f * b->mass;
	if (fa > GRAV_ACCEL_CAP)
		fa = GRAV_ACCEL_CAP;
	b->accel = vec3_add(b->accel, vec3_scale(dir, fa));
}

void	apply_pair_grav(t_physics_body *a, t_physics_body *b, double big_g)
{
	t_vec3	r;
	double	r_sq;
	double	f;
	t_vec3	dir;

	if (a->is_static && b->is_static)
		return ;
	r = vec3_sub(b->pos, a->pos);
	r_sq = vec3_mag_sq(r) + GRAV_SOFT2;
	f = big_g / r_sq;
	dir = vec3_norm(r);
	if (!a->is_static)
		apply_grav_to_body(a, dir, f * b->mass / a->mass);
	if (!b->is_static)
		apply_grav_to_body(b, vec3_scale(dir, -1.0), f * a->mass / b->mass);
}

static void	apply_mag_to_body(t_physics_body *b, t_vec3 d, double f)
{
	double	fa;

	fa = f * b->inv_mass;
	if (fa > GRAV_ACCEL_CAP)
		fa = GRAV_ACCEL_CAP;
	if (fa < -GRAV_ACCEL_CAP)
		fa = -GRAV_ACCEL_CAP;
	b->accel = vec3_add(b->accel, vec3_scale(d, fa));
}

void	apply_pair_mag(t_physics_body *a, t_physics_body *b)
{
	t_vec3	r;
	double	r_sq;
	double	f;
	t_vec3	dir;

	if (a->is_static && b->is_static)
		return ;
	if (a->magnetic_charge == 0.0 && b->magnetic_charge == 0.0)
		return ;
	r = vec3_sub(b->pos, a->pos);
	r_sq = vec3_mag_sq(r) + GRAV_SOFT2;
	f = (a->magnetic_charge * b->magnetic_charge) / r_sq;
	dir = vec3_norm(r);
	if (!a->is_static)
		apply_mag_to_body(a, dir, -f);
	if (!b->is_static)
		apply_mag_to_body(b, dir, f);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Linear Sweep CCD for Sphere vs. Plane.
 * Finds the earliest time t inside [0, 1] that the sphere hits the plane.
 * Prevents tunneling at high velocities.
 */
double	ccd_sweep_sphere_vs_plane(t_vec3 pos, t_vec3 vel, double r,
		t_vec3 pl_pos, t_vec3 pl_norm, double dt)
{
	double	d_start;
	double	v_dot_n;
	double	t;

	d_start = vec3_dot(vec3_sub(pos, pl_pos), pl_norm);
	if (d_start < r)
		return (0.0); /* Already penetrating */
	v_dot_n = vec3_dot(vel, pl_norm);
	if (v_dot_n >= 0.0)
		return (1.0); /* Moving away */
	t = (r - d_start) / (v_dot_n * dt + 1e-9);
	if (t < 0.0 || t > 1.0)
		return (1.0);
	return (t);
}

/**
 * @brief CCD Solver pass. Checks predicted motion against environment.
 * If a hit is detected at t < 1,
	the body's position is clamped to the hit point.
 */
void	phys_resolve_ccd(t_scene *s, int body_idx, double dt)
{
	int					i;
	double				min_t;
	double				t;
	t_vec3				n, pos, vel;
	t_physics_soa		*ps;
	t_primitive_array	*gm;
	int					prim_idx;

	ps = s->physics->soa;
	gm = &s->primitives;
	if (body_idx < 0 || ps->is_static[body_idx])
		return ;
	prim_idx = ps->prim_idx[body_idx];
	vel = vec3(ps->vx[body_idx], ps->vy[body_idx], ps->vz[body_idx]);
	pos = vec3(gm->px[prim_idx], gm->py[prim_idx], gm->pz[prim_idx]);
	if (vec3_mag_sq(vel) < 1.0)
		return ;
	min_t = 1.0;
	i = -1;
	while (++i < (int)gm->count)
	{
		if (gm->types[i] == PRIM_RECT || gm->types[i] == PRIM_PLANE)
		{
			n = vec3(gm->ax[i], gm->ay[i], gm->az[i]);
			t = ccd_sweep_sphere_vs_plane(pos, vel, gm->radii[prim_idx],
					vec3(gm->px[i], gm->py[i], gm->pz[i]), n, dt);
			if (t < min_t)
				min_t = t;
		}
	}
	if (min_t < 1.0)
	{
		gm->px[prim_idx] += (float)(vel.x * min_t * dt);
		gm->py[prim_idx] += (float)(vel.y * min_t * dt);
		gm->pz[prim_idx] += (float)(vel.z * min_t * dt);
		ps->vx[body_idx] *= -0.1f;
		ps->vy[body_idx] *= -0.1f;
		ps->vz[body_idx] *= -0.1f;
	}
}

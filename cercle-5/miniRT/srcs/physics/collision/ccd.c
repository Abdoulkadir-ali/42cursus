/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 17:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

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
	if (d_start < r) return (0.0); /* Already penetrating */
	v_dot_n = vec3_dot(vel, pl_norm);
	if (v_dot_n >= 0.0) return (1.0); /* Moving away */
	t = (r - d_start) / (v_dot_n * dt + 1e-9);
	if (t < 0.0 || t > 1.0) return (1.0);
	return (t);
}

/**
 * @brief CCD Solver pass. Checks predicted motion against environment.
 * If a hit is detected at t < 1, the body's position is clamped to the hit point.
 */
void	phys_resolve_ccd(t_scene *s, t_physics_body *b, double dt)
{
	int		i;
	double	min_t;
	double	t;
	t_vec3	n;

	if (b->is_static || vec3_mag_sq(b->velocity) < 1.0)
		return ;
	min_t = 1.0;
	i = -1;
	while (++i < s->rect_count)
	{
		n = vec3_norm(s->rects[i].transform.up);
		t = ccd_sweep_sphere_vs_plane(b->center, b->velocity, 0.5, 
				s->rects[i].transform.pos, n, dt);
		if (t < min_t) min_t = t;
	}
	if (min_t < 1.0)
	{
		b->center = vec3_add(b->center, vec3_scale(b->velocity, min_t * dt));
		b->velocity = vec3_scale(b->velocity, -0.1); /* Collision early-halt */
	}
}

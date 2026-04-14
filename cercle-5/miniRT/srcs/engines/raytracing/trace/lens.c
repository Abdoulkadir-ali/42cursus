/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 07:11:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	ray_near_black_hole(const t_ray *ray,
				const t_lens_body *bodies, size_t nb)
{
	size_t	i;
	t_vec3	to;
	double	t;
	double	infl_r;

	i = 0;
	while (i < nb)
	{
		infl_r = bodies[i].rs * LENS_INFLUENCE;
		to = vec3_sub(bodies[i].pos, ray->origin);
		t = vec3_dot(to, ray->direction);
		if (!(t < 0.0 && vec3_mag_sq(to) > infl_r * infl_r))
		{
			if (vec3_mag_sq(to) - t * t < infl_r * infl_r)
				return (true);
		}
		i++;
	}
	return (false);
}

static void	update_inv_dir(t_ray *bent)
{
	if (bent->direction.x != 0.0)
		bent->inv_dir.x = 1.0 / bent->direction.x;
	else
		bent->inv_dir.x = 1e30;
	if (bent->direction.y != 0.0)
		bent->inv_dir.y = 1.0 / bent->direction.y;
	else
		bent->inv_dir.y = 1e30;
	if (bent->direction.z != 0.0)
		bent->inv_dir.z = 1.0 / bent->direction.z;
	else
		bent->inv_dir.z = 1e30;
	bent->sign[0] = bent->inv_dir.x < 0;
	bent->sign[1] = bent->inv_dir.y < 0;
	bent->sign[2] = bent->inv_dir.z < 0;
}

static bool	calculate_pull(t_ray *bent, const t_lens_body *bodies,
				size_t nb, double dt)
{
	size_t	i;
	t_vec3	to;
	t_vec3	dv;
	double	r;

	dv = vec3(0, 0, 0);
	i = -1;
	while (++i < nb)
	{
		to = vec3_sub(bodies[i].pos, bent->origin);
		r = sqrt(vec3_mag_sq(to));
		if (r < bodies[i].rs * 1.02)
			return (false);
		dv = vec3_add(dv, vec3_scale(vec3_scale(to, 1.0 / r),
					2.0 * LENS_G_C2 * bodies[i].mass / (r * r) * dt));
	}
	bent->direction = vec3_norm(vec3_add(bent->direction, dv));
	update_inv_dir(bent);
	return (true);
}

bool	march_ray(t_ray *bent, const t_lens_body *bodies, size_t nb)
{
	int		step;
	double	dt;

	step = 0;
	while (step++ < LENS_MAX_STEPS)
	{
		dt = min_dist_to_body(bent->origin, bodies, nb) * LENS_STEP_FRAC;
		if (dt < LENS_STEP_NEAR)
			dt = LENS_STEP_NEAR;
		else if (dt > LENS_STEP_FAR)
			dt = LENS_STEP_FAR;
		if (!calculate_pull(bent, bodies, nb, dt))
			return (false);
		bent->origin = vec3_add(bent->origin, vec3_scale(bent->direction, dt));
		if (!ray_near_black_hole(bent, bodies, nb))
			break ;
	}
	return (true);
}

bool	lens_ray(const t_ray *ray, t_scene *sc, t_ray *out_ray, bool *captured)
{
	t_lens_body	bodies[LENS_MAX_BODIES];
	size_t		nb;

	if (!sc || sc->attractor_count == 0)
	{
		*captured = false;
		return (false);
	}
	*captured = false;
	nb = build_lens_bodies(sc, bodies);
	if (nb == 0)
		return (false);
	*out_ray = *ray;
	if (!ray_near_black_hole(ray, bodies, nb))
		return (false);
	if (!march_ray(out_ray, bodies, nb))
	{
		*captured = true;
		return (true);
	}
	return (true);
}

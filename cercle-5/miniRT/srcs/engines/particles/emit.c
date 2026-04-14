/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:55:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <math.h>
#include <stdlib.h>

/*
** ── Fast pseudo-random helpers ──────────────────────────────────────────────
** LCG seeded from the particle index + alive count.  Returns [0,1).
** Good enough for emission jitter; not cryptographic.
*/
static double	rnd01(unsigned int *seed)
{
	*seed = *seed * 1664525u + 1013904223u;
	return ((double)(*seed >> 1) / 2147483648.0);
}

static double	rnd_range(double lo, double hi, unsigned int *seed)
{
	return (lo + (hi - lo) * rnd01(seed));
}

/*
** Returns a random unit vector uniformly distributed on the sphere surface.
** Uses rejection sampling in the unit cube.
*/
static t_vec3	random_on_sphere(unsigned int *seed)
{
	t_vec3	v;
	double	d;

	while (1)
	{
		v.x = rnd_range(-1.0, 1.0, seed);
		v.y = rnd_range(-1.0, 1.0, seed);
		v.z = rnd_range(-1.0, 1.0, seed);
		d = vec3_mag_sq(v);
		if (d > 1e-6 && d <= 1.0)
			return (vec3_scale(v, 1.0 / sqrt(d)));
	}
}

/*
** Rotates `forward` (0,1,0) onto `dir` using a random cone direction.
** spread = cone half-angle in radians.
*/
static t_vec3	cone_dir(t_vec3 dir, double spread, unsigned int *seed)
{
	t_vec3	perp;
	t_vec3	help;
	t_vec3	out;
	double	phi;
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(spread * rnd01(seed));
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	phi = 2.0 * M_PI * rnd01(seed);
	/* build perpendicular to dir */
	help = (fabs(dir.x) < 0.9) ? vec3(1, 0, 0) : vec3(0, 1, 0);
	perp = vec3_norm(vec3_cross(dir, help));
	/* rotate perp in the cone */
	out = vec3_add(
		vec3_add(
			vec3_scale(perp, sin_theta * cos(phi)),
			vec3_scale(vec3_norm(vec3_cross(dir, perp)), sin_theta * sin(phi))
		),
		vec3_scale(dir, cos_theta)
	);
	return (vec3_norm(out));
}

/*
** Spawns exactly one particle into slot soa->alive (then increments alive).
** Slot is guaranteed to exist (checked by caller).
*/
static void	spawn_one(t_particle_soa *soa, const t_emitter *em,
				unsigned int *seed)
{
	size_t	i;
	t_vec3	launch;

	i = soa->alive;
	if (em->shape == EMITTER_SPHERE_SURF)
	{
		t_vec3 on = random_on_sphere(seed);
		soa->px[i] = em->pos.x + on.x * em->spread;
		soa->py[i] = em->pos.y + on.y * em->spread;
		soa->pz[i] = em->pos.z + on.z * em->spread;
		launch = vec3_scale(on, em->speed);
	}
	else if (em->shape == EMITTER_CONE)
	{
		soa->px[i] = em->pos.x;
		soa->py[i] = em->pos.y;
		soa->pz[i] = em->pos.z;
		t_vec3 d = cone_dir(vec3_norm(em->dir), em->spread, seed);
		launch = vec3_scale(d, em->speed);
	}
	else
	{
		/* EMITTER_POINT */
		soa->px[i] = em->pos.x;
		soa->py[i] = em->pos.y;
		soa->pz[i] = em->pos.z;
		launch = vec3_scale(vec3_norm(em->dir), em->speed);
	}
	soa->vx[i] = launch.x;
	soa->vy[i] = launch.y;
	soa->vz[i] = launch.z;
	soa->age[i] = 0.0;
	soa->life[i] = rnd_range(em->life_min, em->life_max, seed);
	soa->temp[i] = rnd_range(em->temp_min, em->temp_max, seed);
	soa->size[i] = em->size;
	soa->alive++;
}

/*
** Runs one emitter for dt seconds.
** Uses a fractional accumulator so fractional particles carry over to the
** next frame (gives smooth emission at low rates).
*/
void	emit_particles(t_particle_soa *soa, t_emitter *em, double dt)
{
	double		to_spawn;
	int			n;
	unsigned int seed;

	if (!em->active || em->rate <= 0.0)
		return ;
	em->_accum += em->rate * dt;
	to_spawn = em->_accum;
	n = (int)to_spawn;
	em->_accum -= (double)n;
	seed = (unsigned int)(soa->alive * 2654435761u ^ (size_t)(em));
	while (n > 0 && soa->alive < soa->cap)
	{
		spawn_one(soa, em, &seed);
		n--;
	}
}

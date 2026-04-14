/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 11:23:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "particles.h"
#include <math.h>

/*
** ── Gradient noise (value noise with smooth interpolation) ─────────────────
** Returns a pseudo-random scalar in [-1, 1] for a 3D integer lattice point.
** Hash: Wang/Murmur-inspired mix of three integers.
*/
static double	lattice_val(int ix, int iy, int iz)
{
	unsigned int	h;

	h = (unsigned int)ix * 1664525u + 1013904223u;
	h ^= (unsigned int)iy * 22695477u + 1u;
	h ^= (unsigned int)iz * 134775813u + 1u;
	h = (h ^ (h >> 16)) * 0x45d9f3bu;
	h = (h ^ (h >> 16)) * 0x45d9f3bu;
	h ^= h >> 16;
	return ((double)(h & 0xffffu) / 32767.5 - 1.0);
}

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6.0 - 15.0) + 10.0));
}

static double	lerp(double a, double b, double t)
{
	return (a + t * (b - a));
}

/*
** value_noise3: trilinear interpolation of lattice_val at 8 cube corners.
** Returns [-1, 1].  Cheap, deterministic, no lookup table needed.
*/
static double	value_noise3(double x, double y, double z)
{
	int		ix;
	int		iy;
	int		iz;
	double	fx;
	double	fy;
	double	fz;
	double	u;
	double	v;
	double	w;
	double	c[8];

	ix = (int)floor(x);
	iy = (int)floor(y);
	iz = (int)floor(z);
	fx = x - (double)ix;
	fy = y - (double)iy;
	fz = z - (double)iz;
	u = fade(fx);
	v = fade(fy);
	w = fade(fz);
	c[0] = lattice_val(ix, iy, iz);
	c[1] = lattice_val(ix + 1, iy, iz);
	c[2] = lattice_val(ix, iy + 1, iz);
	c[3] = lattice_val(ix + 1, iy + 1, iz);
	c[4] = lattice_val(ix, iy, iz + 1);
	c[5] = lattice_val(ix + 1, iy, iz + 1);
	c[6] = lattice_val(ix, iy + 1, iz + 1);
	c[7] = lattice_val(ix + 1, iy + 1, iz + 1);
	return (lerp(lerp(lerp(c[0], c[1], u), lerp(c[2], c[3], u), v),
			lerp(lerp(c[4], c[5], u), lerp(c[6], c[7], u), v), w));
}

/*
** turbulence_offset: 2-octave FBM noise offset applied to the body's position
** so neighbouring bodies feel slightly different gusts.
*/
static t_vec3	turbulence_offset(t_vec3 pos, double turb, double t)
{
	t_vec3	off;
	double	s1;
	double	s2;

	if (turb < 1e-9)
		return (vec3(0, 0, 0));
	/* octave 1: world-space position + time */
	s1 = value_noise3(pos.x * 0.3 + t * 1.1,
			pos.y * 0.3 + t * 0.7,
			pos.z * 0.3 + t * 0.9);
	/* octave 2: higher frequency, lower amplitude */
	s2 = value_noise3(pos.x * 0.7 + t * 2.3 + 17.3,
			pos.y * 0.7 + t * 1.9 + 5.1,
			pos.z * 0.7 + t * 2.1 + 11.7) * 0.5;
	off.x = (s1 + s2) * turb;
	/* Y component: gentler vertical gusts */
	s1 = value_noise3(pos.x * 0.3 + t * 0.8 + 31.0,
			pos.y * 0.3 + t * 1.2 + 7.0,
			pos.z * 0.3 + t * 1.0 + 3.0);
	off.y = s1 * turb * 0.4;
	/* Z component: mirrored X with phase shift */
	s1 = value_noise3(pos.x * 0.3 + t * 1.3 + 53.0,
			pos.y * 0.3 + t * 0.6 + 23.0,
			pos.z * 0.3 + t * 1.4 + 41.0);
	s2 = value_noise3(pos.x * 0.7 + t * 2.7 + 9.0,
			pos.y * 0.7 + t * 2.1 + 37.0,
			pos.z * 0.7 + t * 1.8 + 19.0) * 0.5;
	off.z = (s1 + s2) * turb;
	return (off);
}

/*
** wind_accel_at: returns the total wind acceleration (wind + turbulence) for
** a given world position and the current wind_time.
*/
static t_vec3	wind_accel_at(t_vec3 pos, const t_physics_settings *s)
{
	t_vec3	w;
	t_vec3	tb;

	w = s->wind;
	tb = turbulence_offset(pos, s->wind_turbulence, s->wind_time);
	return (vec3_add(w, tb));
}

/* ── Collects every movable body pointer (mirrors fill_bodies in attractor) ─ */

static void	apply_wind_to_physics_body(t_physics_body *b,
				const t_physics_settings *s, double dt)
{
	t_vec3	w;

	if (!b || b->is_static || b->is_sleeping)
		return ;
	w = vec3_scale(wind_accel_at(b->pos, s), dt);
	b->velocity = vec3_add(b->velocity, w);
}

/*
** apply_wind_to_soft_body: injects wind force on every free (non-pinned)
** particle of every soft body.  Called inside soft_body_step's substep loop
** — wind.c makes it public so worker.c can call it before the substep to
** update s->wind_time and let soft_body.c read the updated settings.
*/
static void	apply_wind_to_soft_bodies(t_scene *scene,
				const t_physics_settings *s)
{
	t_soft_body	*sb;
	t_vec3		w;
	size_t		sb_i;
	size_t		p_i;

	sb_i = 0;
	while (sb_i < scene->soft_body_count)
	{
		sb = &scene->soft_bodies[sb_i];
		p_i = 0;
		while (p_i < sb->particle_count)
		{
			if (sb->particles[p_i].inv_mass > 0.0)
			{
				w = wind_accel_at(sb->particles[p_i].pos, s);
				sb->particles[p_i].force = vec3_add(
					sb->particles[p_i].force,
					vec3_scale(w, 1.0 / sb->particles[p_i].inv_mass));
			}
			p_i++;
		}
		sb_i++;
	}
}

/*
** apply_wind_to_particles: injects wind into the SoA particle velocity buffer.
** Turbulence is sampled from each particle's position for "swirling" effect.
*/
static void	apply_wind_to_particles(t_particle_soa *soa,
				const t_physics_settings *s, double dt)
{
	t_vec3	pos;
	t_vec3	w;
	size_t	i;

	if (!soa || soa->alive == 0)
		return ;
	i = 0;
	while (i < soa->alive)
	{
		pos = vec3(soa->px[i], soa->py[i], soa->pz[i]);
		w = vec3_scale(wind_accel_at(pos, s), dt);
		soa->vx[i] += w.x;
		soa->vy[i] += w.y;
		soa->vz[i] += w.z;
		i++;
	}
}

/*
** apply_wind_pass: top-level entry called from worker.c immediately before
** the integration pass.  Runs if wind magnitude + turbulence > epsilon.
**
** Advances wind_time by dt (so gusts evolve over time).
*/
void	apply_wind_pass(t_scene *scene, t_physics_settings *s, double dt)
{
	size_t	i;

	if (vec3_mag_sq(s->wind) < 1e-9 && s->wind_turbulence < 1e-9)
		return ;
	s->wind_time += dt;
	/* Rigid bodies */
	i = 0;
	while (i < scene->sphere_count - scene->proxy_sphere_count)
		apply_wind_to_physics_body(&scene->spheres[i++].phys, s, dt);
	i = 0;
	while (i < scene->box_count)
		apply_wind_to_physics_body(&scene->boxes[i++].phys, s, dt);
	i = 0;
	while (i < scene->cylinder_count)
		apply_wind_to_physics_body(&scene->cylinders[i++].phys, s, dt);
	i = 0;
	while (i < scene->capsule_count)
		apply_wind_to_physics_body(&scene->capsules[i++].phys, s, dt);
	i = 0;
	while (i < scene->pyramid_count)
		apply_wind_to_physics_body(&scene->pyramids[i++].phys, s, dt);
	i = 0;
	while (i < scene->rect_count)
		apply_wind_to_physics_body(&scene->rects[i++].phys, s, dt);
	i = 0;
	while (i < scene->tri_count)
		apply_wind_to_physics_body(&scene->tris[i++].phys, s, dt);
	/* Soft bodies (force-based, must run BEFORE accumulate_forces resets) */
	apply_wind_to_soft_bodies(scene, s);
	/* SoA particles */
	if (scene->psoa)
		apply_wind_to_particles(scene->psoa, s, dt);
}

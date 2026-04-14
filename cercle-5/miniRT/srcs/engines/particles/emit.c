/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <math.h>
#include <stdlib.h>

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

static t_vec3	cone_dir(t_vec3 dir, double spread, unsigned int *seed)
{
	t_vec3	p[3];
	t_vec3	help;
	double	v[3];

	v[0] = cos(spread * rnd01(seed));
	v[1] = sqrt(1.0 - v[0] * v[0]);
	v[2] = 2.0 * M_PI * rnd01(seed);
	help = vec3(0, 1, 0);
	if (fabs(dir.x) < 0.9)
		help = vec3(1, 0, 0);
	p[0] = vec3_norm(vec3_cross(dir, help));
	p[1] = vec3_norm(vec3_cross(dir, p[0]));
	p[2] = vec3_add(
			vec3_add(
				vec3_scale(p[0], v[1] * cos(v[2])),
				vec3_scale(p[1], v[1] * sin(v[2]))),
			vec3_scale(dir, v[0]));
	return (vec3_norm(p[2]));
}

static void	spawn_props(t_particle_soa *soa, const t_emitter *em,
				unsigned int *seed, t_vec3 launch)
{
	size_t	i;

	i = soa->alive;
	soa->vx[i] = launch.x;
	soa->vy[i] = launch.y;
	soa->vz[i] = launch.z;
	soa->age[i] = 0.0;
	soa->life[i] = rnd_range(em->life_min, em->life_max, seed);
	soa->temp[i] = rnd_range(em->temp_min, em->temp_max, seed);
	soa->size[i] = em->size;
	soa->alive++;
}

static void	set_spawn_pos(t_particle_soa *s, const t_emitter *e,
				unsigned int *sd, t_vec3 *l)
{
	t_vec3	on;
	size_t	i;

	i = s->alive;
	if (e->shape == EMITTER_SPHERE_SURF)
	{
		on = random_on_sphere(sd);
		s->px[i] = e->pos.x + on.x * e->spread;
		s->py[i] = e->pos.y + on.y * e->spread;
		s->pz[i] = e->pos.z + on.z * e->spread;
		*l = vec3_scale(on, e->speed);
		return ;
	}
	s->px[i] = e->pos.x;
	s->py[i] = e->pos.y;
	s->pz[i] = e->pos.z;
	if (e->shape == EMITTER_CONE)
		*l = vec3_scale(cone_dir(vec3_norm(e->dir), e->spread, sd), e->speed);
	else
		*l = vec3_scale(vec3_norm(e->dir), e->speed);
}

void	emit_particles(t_particle_soa *soa, t_emitter *em, double dt)
{
	int				n;
	unsigned int	seed;
	t_vec3			launch;

	if (!em->active || em->rate <= 0.0)
		return ;
	em->_accum += em->rate * dt;
	n = (int)em->_accum;
	em->_accum -= (double)n;
	seed = (unsigned int)(soa->alive * 2654435761u ^ (size_t)(em));
	while (n > 0 && soa->alive < soa->cap)
	{
		set_spawn_pos(soa, em, &seed, &launch);
		spawn_props(soa, em, &seed, launch);
		n--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "mesh.h"
#include "scene.h"
#include <stdlib.h>

static void	writeback(t_soft_body *sb, t_mesh *mesh)
{
	size_t	i;

	i = 0;
	while (i < sb->particle_count)
	{
		mesh->vertices[i].pos = sb->particles[i].pos;
		i++;
	}
}

static void	integrate_particles(t_soft_body *sb, double dt,
	const t_physics_settings *s)
{
	size_t			i;
	t_sb_particle	*p;
	double			linear_d;
	double			spd;

	linear_d = fmax(0.0, 1.0 - s->global_damping * dt);
	i = 0;
	while (i < sb->particle_count)
	{
		p = &sb->particles[i];
		if (p->inv_mass > 0.0)
		{
			p->vel = vec3_add(p->vel, vec3_scale(p->force, p->inv_mass * dt));
			p->vel = vec3_scale(p->vel, linear_d);
			spd = vec3_mag(p->vel);
			if (spd > 15.0)
				p->vel = vec3_scale(p->vel, 15.0 / spd);
			p->pos = vec3_add(p->pos, vec3_scale(p->vel, dt));
		}
		i++;
	}
}

static void	soft_body_sub_step(t_scene *sc, t_soft_body *sb, double dt,
	t_physics_settings *s)
{
	size_t	j;

	accumulate_ext_f(sb, s);
	accumulate_spring_f(sb);
	j = -1;
	while (++j < sc->sphere_count - sc->proxy_sphere_count)
		if (!sc->spheres[j].phys.is_static)
			apply_one_body_to_sb(sb, sc->spheres[j].phys.pos,
				s->big_g * sc->spheres[j].phys.mass);
	apply_vols_to_sb(sb, sc, s->big_g);
	apply_surfs_to_sb(sb, sc, s->big_g);
	integrate_particles(sb, dt, s);
}

void	soft_body_step(t_scene *sc, double dt, t_physics_settings *s)
{
	size_t		i;
	t_soft_body	*sb;
	int			st;

	i = -1;
	while (++i < sc->soft_body_count)
	{
		sb = &sc->soft_bodies[i];
		if (!sb->active || sb->mesh_idx >= sc->mesh_count)
			continue ;
		st = -1;
		while (++st < 10)
			soft_body_sub_step(sc, sb, dt / 10.0, s);
		writeback(sb, &sc->meshes[sb->mesh_idx]);
	}
}

void	soft_body_free(t_soft_body *sb)
{
	if (!sb)
		return ;
	free(sb->particles);
	free(sb->springs);
	sb->particles = NULL;
	sb->springs = NULL;
	sb->active = false;
}

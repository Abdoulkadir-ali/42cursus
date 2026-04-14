/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <math.h>

static void	p_phys(t_particle_soa *soa, t_scene *sc, double dt,
				const t_physics_settings *s)
{
	size_t	i;
	t_vec3	g;

	g = vec3_scale(s->gravity, dt);
	i = 0;
	while (i < soa->alive)
	{
		soa->vx[i] += g.x;
		soa->vy[i] += g.y;
		soa->vz[i] += g.z;
		i++;
	}
	particle_apply_attractors(soa, sc, s->big_g);
	particle_apply_rigid_bodies(soa, sc, s->big_g);
	i = 0;
	while (i < soa->alive)
	{
		soa->px[i] += soa->vx[i] * dt;
		soa->py[i] += soa->vy[i] * dt;
		soa->pz[i] += soa->vz[i] * dt;
		i++;
	}
}

void	particle_systems_step(t_scene *scene, double dt,
			const t_physics_settings *s)
{
	t_particle_soa	*soa;
	size_t			i;

	if (!scene || !scene->psoa || dt < 1e-9)
		return ;
	if (!scene->psoa_ready)
		init_proxy_spheres(scene);
	soa = scene->psoa;
	i = 0;
	while (i < scene->emitter_count)
		emit_particles(soa, &scene->emitters[i++], dt);
	if (soa->alive == 0)
	{
		update_proxy_spheres(scene);
		return ;
	}
	p_phys(soa, scene, dt, s);
	age_and_kill(soa, dt);
	update_proxy_spheres(scene);
}

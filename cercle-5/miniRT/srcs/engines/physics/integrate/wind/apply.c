/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "particles.h"

void	apply_wind_vols(t_scene *sc, const t_physics_settings *s, double dt)
{
	size_t	i;

	i = 0;
	while (i < sc->sphere_count - sc->proxy_sphere_count)
		apply_wind_to_physics_body(&sc->spheres[i++].phys, s, dt);
	i = 0;
	while (i < sc->box_count)
		apply_wind_to_physics_body(&sc->boxes[i++].phys, s, dt);
	i = 0;
	while (i < sc->cylinder_count)
		apply_wind_to_physics_body(&sc->cylinders[i++].phys, s, dt);
	i = 0;
	while (i < sc->capsule_count)
		apply_wind_to_physics_body(&sc->capsules[i++].phys, s, dt);
}

void	apply_wind_surfs(t_scene *sc, const t_physics_settings *s, double dt)
{
	size_t	i;

	i = 0;
	while (i < sc->pyramid_count)
		apply_wind_to_physics_body(&sc->pyramids[i++].phys, s, dt);
	i = 0;
	while (i < sc->rect_count)
		apply_wind_to_physics_body(&sc->rects[i++].phys, s, dt);
	i = 0;
	while (i < sc->tri_count)
		apply_wind_to_physics_body(&sc->tris[i++].phys, s, dt);
}

void	apply_wind_to_soft_bodies(t_scene *scene,
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

void	apply_wind_to_particles(t_particle_soa *soa,
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

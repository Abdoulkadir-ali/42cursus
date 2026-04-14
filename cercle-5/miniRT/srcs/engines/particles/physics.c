/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:55:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <math.h>

/*
** Adds Newtonian acceleration from a massive point (pos, g_mass = G*M) to
** every live particle.  Plummer-softened to avoid singularity.
*/
static void	pull_from_point(t_particle_soa *soa, t_vec3 at, double g_mass)
{
	t_vec3	r;
	double	r_sq;
	double	accel;
	size_t	i;

	i = 0;
	while (i < soa->alive)
	{
		r.x = at.x - soa->px[i];
		r.y = at.y - soa->py[i];
		r.z = at.z - soa->pz[i];
		r_sq = r.x * r.x + r.y * r.y + r.z * r.z + PART_GRAV_SOFT2;
		accel = g_mass / r_sq;
		if (accel > PART_GRAV_ACCEL_CAP)
			accel = PART_GRAV_ACCEL_CAP;
		r_sq = 1.0 / sqrt(r_sq);
		soa->vx[i] += r.x * r_sq * accel;
		soa->vy[i] += r.y * r_sq * accel;
		soa->vz[i] += r.z * r_sq * accel;
		i++;
	}
}

/*
** Applies all explicit attractors (bh / at keywords) to particles.
*/
void	particle_apply_attractors(t_particle_soa *soa, t_scene *scene,
			double big_g)
{
	size_t	i;

	if (!scene || scene->attractor_count == 0 || big_g < 1e-30)
		return ;
	i = 0;
	while (i < scene->attractor_count)
	{
		pull_from_point(soa, scene->attractors[i].pos,
			big_g * scene->attractors[i].mass);
		i++;
	}
}

static void	apply_spheres(t_particle_soa *soa, t_scene *scene, double big_g)
{
	size_t	i;

	i = 0;
	while (i < scene->sphere_count - scene->proxy_sphere_count)
	{
		if (!scene->spheres[i].phys.is_static)
			pull_from_point(soa, scene->spheres[i].phys.pos,
				big_g * scene->spheres[i].phys.mass);
		i++;
	}
}

static void	apply_complex(t_particle_soa *soa, t_scene *scene, double big_g)
{
	size_t	i;

	i = -1;
	while (++i < scene->box_count)
		if (!scene->boxes[i].phys.is_static)
			pull_from_point(soa, scene->boxes[i].phys.pos,
				big_g * scene->boxes[i].phys.mass);
	i = -1;
	while (++i < scene->cylinder_count)
		if (!scene->cylinders[i].phys.is_static)
			pull_from_point(soa, scene->cylinders[i].phys.pos,
				big_g * scene->cylinders[i].phys.mass);
	i = -1;
	while (++i < scene->capsule_count)
		if (!scene->capsules[i].phys.is_static)
			pull_from_point(soa, scene->capsules[i].phys.pos,
				big_g * scene->capsules[i].phys.mass);
}

/*
** Applies N-body gravitational pull from all dynamic rigid bodies.
** Mirrors apply_bodies_to_sb() in soft_body.c.
*/
void	particle_apply_rigid_bodies(t_particle_soa *soa, t_scene *scene,
			double big_g)
{
	if (!scene || big_g < 1e-30)
		return ;
	apply_spheres(soa, scene, big_g);
	apply_complex(soa, scene, big_g);
}

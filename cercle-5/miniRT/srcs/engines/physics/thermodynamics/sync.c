/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thermal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

#define THERMAL_G_C2   1e-8
#define THERMAL_COLLAPSE_THRESHOLD  1.0

static void	sync_one(t_physics_body *phys, size_t mat_id, t_scene *sc)
{
	if (phys->is_static || phys->temperature <= 0.0)
		return ;
	if (mat_id >= sc->mat_count)
		return ;
	sc->materials[mat_id].temperature = phys->temperature;
	apply_blackbody_to_mat(&sc->materials[mat_id]);
}

static void	sphere_collapse_step(t_sphere *sp)
{
	double	rs;
	double	radius;
	double	target_r;

	if (sp->phys.is_static || sp->phys.mass <= 0.0)
		return ;
	rs = 2.0 * THERMAL_G_C2 * sp->phys.mass;
	if (rs >= THERMAL_COLLAPSE_THRESHOLD)
	{
		radius = sqrt(sp->radius_sq);
		target_r = rs;
		if (rs < 0.05)
			target_r = 0.05;
		if (target_r < radius)
		{
			radius = radius * 0.92 + target_r * 0.08;
			sp->radius_sq = radius * radius;
		}
	}
}

static void	sync_vols(t_scene *sc)
{
	size_t	i;

	i = 0;
	while (i < sc->sphere_count)
	{
		sync_one(&sc->spheres[i].phys, sc->spheres[i].mat_id, sc);
		sphere_collapse_step(&sc->spheres[i]);
		i++;
	}
	i = 0;
	while (i < sc->box_count)
	{
		sync_one(&sc->boxes[i].phys, sc->boxes[i].mat_id, sc);
		i++;
	}
}

static void	sync_surfs(t_scene *sc)
{
	size_t	i;

	i = 0;
	while (i < sc->capsule_count)
	{
		sync_one(&sc->capsules[i].phys, sc->capsules[i].mat_id, sc);
		i++;
	}
	i = 0;
	while (i < sc->cylinder_count)
	{
		sync_one(&sc->cylinders[i].phys, sc->cylinders[i].mat_id, sc);
		i++;
	}
	i = 0;
	while (i < sc->pyramid_count)
	{
		sync_one(&sc->pyramids[i].phys, sc->pyramids[i].mat_id, sc);
		i++;
	}
}

void	sync_thermal_to_materials(t_scene *sc)
{
	size_t	i;

	if (!sc)
		return ;
	sync_vols(sc);
	sync_surfs(sc);
	i = 0;
	while (i < sc->rect_count)
	{
		sync_one(&sc->rects[i].phys, sc->rects[i].mat_id, sc);
		i++;
	}
	i = 0;
	while (i < sc->tri_count)
	{
		sync_one(&sc->tris[i].phys, sc->tris[i].mat_id, sc);
		i++;
	}
}

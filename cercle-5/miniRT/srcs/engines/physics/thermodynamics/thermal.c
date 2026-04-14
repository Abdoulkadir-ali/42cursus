/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thermal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 13:24:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

/*
** Rotational/viscous drag heats the body: T += DRAG * |ω|² * dt
** At |ω|=10 rad/s  →   0.5 K/s
** At |ω|=100 rad/s →  50  K/s
** At |ω|=500 rad/s → 1250 K/s (visibly glowing after a few seconds)
*/
# define PHYS_DRAG_COEFF    5e-4

/*
** Stefan-Boltzmann radiative cooling (implicit, numerically stable):
** T_new = T / (1 + COOL * T³ * dt)
** At 1000K  →  ~0.5 K/s loss
** At 6500K  →  ~89  K/s loss
** At 50000K →  enormous — objects cannot sustain absurd temps
*/
# define PHYS_COOL_COEFF    5e-13

/*
** Collision heating: lost KE = (1-e) * j² / (mass_a + mass_b)
** Fraction converted to heat (unitless scale factor):
*/
# define PHYS_COLL_COEFF    0.05

void	phys_heat_viscous(t_physics_body *b, double dt)
{
	double	w_sq;

	if (!b || b->is_static || b->is_sleeping)
		return ;
	w_sq = vec3_mag_sq(b->angular_velocity);
	b->temperature += PHYS_DRAG_COEFF * w_sq * dt;
}

void	phys_cool_radiative(t_physics_body *b, double dt)
{
	double	t3;

	if (!b || b->is_static || b->temperature < 1.0)
		return ;
	t3 = b->temperature * b->temperature * b->temperature;
	b->temperature /= (1.0 + PHYS_COOL_COEFF * t3 * dt);
	if (b->temperature < 1.0)
		b->temperature = 0.0;
}

/*
** Called from the velocity solver with the computed normal impulse j.
** ΔT = (1 - restitution) * j² * COLL_COEFF / avg_mass
** Split equally between both bodies.
*/
void	phys_heat_collision(t_contact *ct, double j, double e)
{
	double	heat;
	double	avg_mass;

	if (j < 0.1)
		return ;
	avg_mass = 1.0;
	if (ct->a && !ct->a->is_static && ct->a->mass > 1e-6)
		avg_mass = ct->a->mass;
	else if (ct->b && !ct->b->is_static && ct->b->mass > 1e-6)
		avg_mass = ct->b->mass;
	heat = (1.0 - e) * j * j * PHYS_COLL_COEFF / avg_mass;
	if (heat < 0.01)
		return ;
	if (ct->a && !ct->a->is_static)
		ct->a->temperature += heat;
	if (ct->b && !ct->b->is_static)
		ct->b->temperature += heat;
}

/*
** Writes phys.temperature → mat->temperature for every non-static object,
** then calls apply_blackbody_to_mat so emission RGB + power update immediately.
** Static objects are untouched (manual slider controls them).
*/
static void	sync_one(t_physics_body *phys, size_t mat_id, t_scene *sc)
{
	if (phys->is_static || phys->temperature <= 0.0)
		return ;
	if (mat_id >= sc->mat_count)
		return ;
	sc->materials[mat_id].temperature = phys->temperature;
	apply_blackbody_to_mat(&sc->materials[mat_id]);
}

/*
** Gravitational collapse: when Rs = 2*G_C2*phys.mass < geometric radius,
** the sphere is denser than its own Schwarzschild limit — it compresses.
** We smoothly shrink radius_sq toward Rs² so the sphere becomes a tight,
** dense point rather than a wide black disc.
** G_C2 must match LENS_G_C2 in lens.c.
*/
# define THERMAL_G_C2   1e-8

/*
** Same threshold as LENS_MIN_RS in lens.c.
** A sphere only compresses when its Schwarzschild radius is >= 1 scene unit,
** meaning mass >= 5e7. Normal physics objects (mass 1-10000) are unaffected.
*/
# define THERMAL_COLLAPSE_THRESHOLD  1.0

static void	sync_collapse_radii(t_scene *sc)
{
	size_t	i;
	double	rs;
	double	radius;
	double	target_r;

	i = 0;
	while (i < sc->sphere_count)
	{
		if (!sc->spheres[i].phys.is_static && sc->spheres[i].phys.mass > 0.0)
		{
			rs = 2.0 * THERMAL_G_C2 * sc->spheres[i].phys.mass;
			/*
			** Only trigger when Rs is astronomically significant (>= 1 unit).
			** Rs = 1 requires mass >= 5e7. Normal objects (mass < 1e6) never
			** collapse. The sphere shrinks toward its Schwarzschild radius —
			** tinier and denser as mass grows.
			*/
			if (rs >= THERMAL_COLLAPSE_THRESHOLD)
			{
				radius = sqrt(sc->spheres[i].radius_sq);
				target_r = rs < 0.05 ? 0.05 : rs;
				if (target_r < radius)
				{
					radius = radius * 0.92 + target_r * 0.08;
					sc->spheres[i].radius_sq = radius * radius;
				}
			}
		}
		i++;
	}
}

void	sync_thermal_to_materials(t_scene *sc)
{
	size_t	i;

	if (!sc)
		return ;
	i = 0;
	while (i < sc->sphere_count)
	{
		sync_one(&sc->spheres[i].phys, sc->spheres[i].mat_id, sc);
		i++;
	}
	i = 0;
	while (i < sc->box_count)
	{
		sync_one(&sc->boxes[i].phys, sc->boxes[i].mat_id, sc);
		i++;
	}
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
	sync_collapse_radii(sc);
}

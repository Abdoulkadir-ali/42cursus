/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	build_attractors(t_scene *sc, t_lens_body bodies[LENS_MAX_BODIES],
				size_t *nb)
{
	size_t	i;
	double	rs;

	i = 0;
	while (i < sc->attractor_count && *nb < LENS_MAX_BODIES)
	{
		rs = schwarzschild_r(sc->attractors[i].mass);
		if (sc->attractors[i].is_black_hole || rs >= LENS_MIN_RS)
		{
			bodies[*nb].pos = sc->attractors[i].pos;
			bodies[*nb].mass = sc->attractors[i].mass;
			bodies[*nb].rs = rs;
			(*nb)++;
		}
		i++;
	}
}

static void	build_spheres(t_scene *sc, t_lens_body bodies[LENS_MAX_BODIES],
				size_t *nb)
{
	size_t	i;
	double	rs;
	double	radius;

	i = 0;
	while (i < sc->sphere_count && *nb < LENS_MAX_BODIES)
	{
		if (sc->spheres[i].phys.mass > 0.0)
		{
			radius = sqrt(sc->spheres[i].radius_sq);
			rs = schwarzschild_r(sc->spheres[i].phys.mass);
			if (rs >= radius)
			{
				bodies[*nb].pos = sc->spheres[i].transform.pos;
				bodies[*nb].mass = sc->spheres[i].phys.mass;
				bodies[*nb].rs = radius;
				(*nb)++;
			}
		}
		i++;
	}
}

size_t	build_lens_bodies(t_scene *sc, t_lens_body bodies[LENS_MAX_BODIES])
{
	size_t	nb;

	nb = 0;
	build_attractors(sc, bodies, &nb);
	build_spheres(sc, bodies, &nb);
	return (nb);
}

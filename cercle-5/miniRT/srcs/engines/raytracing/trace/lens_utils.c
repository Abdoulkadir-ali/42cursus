/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

double	schwarzschild_r(double mass)
{
	return (2.0 * LENS_G_C2 * mass);
}

bool	point_inside_eh(t_vec3 pos, t_scene *sc)
{
	size_t	i;
	double	rs;
	double	r2;

	if (!sc)
		return (false);
	i = 0;
	while (i < sc->attractor_count)
	{
		rs = schwarzschild_r(sc->attractors[i].mass);
		if (rs >= LENS_MIN_RS)
		{
			r2 = vec3_mag_sq(vec3_sub(pos, sc->attractors[i].pos));
			if (r2 < rs * rs)
				return (true);
		}
		i++;
	}
	return (false);
}

double	min_dist_to_body(t_vec3 pos, const t_lens_body *bodies,
				size_t nb)
{
	size_t	i;
	double	r;
	double	min_r;

	min_r = 1e30;
	i = 0;
	while (i < nb)
	{
		r = sqrt(vec3_mag_sq(vec3_sub(bodies[i].pos, pos))) - bodies[i].rs;
		if (r < min_r)
			min_r = r;
		i++;
	}
	if (min_r < 0.0)
		return (0.0);
	return (min_r);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	count_spheres(t_scene *sc)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (i < sc->primitives.count)
	{
		if (sc->primitives.types[i] == PRIM_SPHERE)
			count++;
		i++;
	}
	return (count);
}

static void	extract_spheres(t_scene *sc, t_sphere *dst)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < sc->primitives.count)
	{
		if (sc->primitives.types[i] == PRIM_SPHERE)
		{
			dst[j].transform.pos = vec3(sc->primitives.px[i],
					sc->primitives.py[i], sc->primitives.pz[i]);
			dst[j].radius_sq = (double)sc->primitives.radii[i]
				* sc->primitives.radii[i];
			dst[j].mat_id = sc->primitives.mat_ids[i];
			if (sc->primitives.physics[i])
				dst[j].phys = *sc->primitives.physics[i];
			j++;
		}
		i++;
	}
}

/**
 * @brief Captures spheres from SoA into the editor's AoS snapshot.
 */
void	snap_sphere(t_scene_snap *s, t_scene *sc)
{
	s->sphere_count = count_spheres(sc);
	s->spheres = NULL;
	if (s->sphere_count > 0)
	{
		s->spheres = malloc(sizeof(t_sphere) * s->sphere_count);
		if (s->spheres)
			extract_spheres(sc, s->spheres);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	count_planes(t_scene *sc)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (i < sc->primitives.count)
	{
		if (sc->primitives.types[i] == PRIM_PLANE)
			count++;
		i++;
	}
	return (count);
}

static void	extract_planes(t_scene *sc, t_plane *dst)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < sc->primitives.count)
	{
		if (sc->primitives.types[i] == PRIM_PLANE)
		{
			dst[j].transform.pos = vec3(sc->primitives.px[i],
					sc->primitives.py[i], sc->primitives.pz[i]);
			dst[j].normal = vec3(sc->primitives.ax[i],
					sc->primitives.ay[i], sc->primitives.az[i]);
			dst[j].mat_id = sc->primitives.mat_ids[i];
			j++;
		}
		i++;
	}
}

/**
 * @brief Captures planes from SoA into the editor's AoS snapshot.
 */
void	snap_plane(t_scene_snap *s, t_scene *sc)
{
	s->plane_count = count_planes(sc);
	s->planes = NULL;
	if (s->plane_count > 0)
	{
		s->planes = malloc(sizeof(t_plane) * s->plane_count);
		if (s->planes)
			extract_planes(sc, s->planes);
	}
}

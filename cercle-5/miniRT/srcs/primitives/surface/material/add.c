/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "scene.h"

/**
 * @brief Safely adds a material by recycling identical ones if they exist.
 * @param sc Pointer to the scene.
 * @param color The base color requested.
 * @return int The index of the recycled or new material.
 */
int	scene_add_material(t_scene *sc, t_vec3 color)
{
	int			i;
	t_material	*m;

	i = 0;
	while (i < sc->mat_count)
	{
		m = &sc->materials[i];
		if (m->albedo_map.type == TEX_SOLID
			&& vec3_compare(m->albedo_map.color_a, color)
			&& vec3_mag_sq(m->emission) < EPSILON)
			return (i);
		i++;
	}
	return (scene_add_fresh_material(sc, color));
}

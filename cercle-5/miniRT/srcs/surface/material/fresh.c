/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "scene.h"

/**
 * @brief Adds a new, clean material to the scene.
 * @param sc Pointer to the scene.
 * @param color The base color for the material.
 * @return int The index of the added material, or -1 on failure.
 */
int	scene_add_fresh_material(t_scene *sc, t_vec3 color)
{
	t_material	*m;

	if (!DYNARRAY_ENSURE_INT(&sc->materials, &sc->mat_count,
			&sc->mat_cap, sizeof(t_material)))
		return (-1);
	m = &sc->materials[sc->mat_count];
	ft_memset(m, 0, sizeof(t_material));
	m->albedo_map.type = TEX_SOLID;
	m->albedo_map.color_a = color;
	m->albedo_map.scale = 1.0;
	m->specular = 0.5;
	m->shininess = 32.0;
	material_apply_preset(m, color);
	return (sc->mat_count++);
}

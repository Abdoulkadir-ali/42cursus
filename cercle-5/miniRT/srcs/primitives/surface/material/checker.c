/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
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
 * @brief Creates a UE-style default checkerboard material.
 * @param sc Pointer to the scene.
 * @param color_a Dark gray color.
 * @param color_b Light gray color.
 * @param scale The size of the quadrants.
 * @return int Index of the added material, or -1 on failure.
 */
int	scene_add_checker_material(t_scene *sc, t_vec3 color_a,
		t_vec3 color_b, double scale)
{
	t_material	*m;

	if (!DYNARRAY_ENSURE_INT(&sc->materials, &sc->mat_count,
			&sc->mat_cap, sizeof(t_material)))
		return (-1);
	m = &sc->materials[sc->mat_count];
	ft_memset(m, 0, sizeof(t_material));
	m->albedo_map.type = TEX_CHECKER;
	m->albedo_map.color_a = color_a;
	m->albedo_map.color_b = color_b;
	m->albedo_map.scale = scale;
	m->specular = 0.3;
	m->shininess = 16.0;
	return (sc->mat_count++);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   named.c                                            :+:      :+:    :+:   */
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
 * @brief Creates a new named material in the scene.
 * @param sc Pointer to the scene.
 * @param name Name of the new material.
 * @return int Index of the added material, or -1 on failure.
 */
int	scene_add_named_material(t_scene *sc, const char *name)
{
	t_material	*m;

	if (!DYNARRAY_ENSURE_INT(&sc->materials, &sc->mat_count,
			&sc->mat_cap, sizeof(t_material)))
		return (-1);
	m = &sc->materials[sc->mat_count];
	ft_memset(m, 0, sizeof(t_material));
	m->name = ft_strdup(name);
	m->albedo_map.type = TEX_SOLID;
	m->albedo_map.color_a = (t_vec3){255.0, 255.0, 255.0};
	m->albedo_map.scale = 1.0;
	m->specular = 0.1;
	m->shininess = 16.0;
	return (sc->mat_count++);
}

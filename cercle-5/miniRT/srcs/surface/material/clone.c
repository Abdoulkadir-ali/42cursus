/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
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
 * @brief Clones an existing material by ID.
 * @param sc Pointer to the scene.
 * @param src_id Index of the material to clone.
 * @return int The index of the new material, or -1 on failure.
 */
int	scene_clone_material(t_scene *sc, int src_id)
{
	if (src_id < 0 || src_id >= sc->mat_count)
		return (scene_add_fresh_material(sc, (t_vec3){255.0, 255.0, 255.0, 0.0}));
	if (!DYNARRAY_ENSURE_INT(&sc->materials, &sc->mat_count,
			&sc->mat_cap, sizeof(t_material)))
		return (-1);
	sc->materials[sc->mat_count] = sc->materials[src_id];
	sc->materials[sc->mat_count].name = NULL;
	return (sc->mat_count++);
}

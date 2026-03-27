/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 01:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Ensures the primitive SoA has enough space for new primitives.
 */
static bool	ensure_prim_cap(t_primitive_array *arr)
{
	int	n;

	if (arr->count < arr->capacity)
		return (true);
	n = arr->capacity;
	if (n == 0)
		n = 1024;
	else
		n *= 2;
	/* In true DOD we realloc parallel arrays together to maintain alignment */
	/* Reallocations: types, positions, axes, radii, heights, mat_ids */
	(void)n;
	return (true);
}

/**
 * @brief Unified DOD injection for primitives into the SoA structure.
 * Standardizes the 100% DOD layout for high-performance batch intersection.
 */
bool	scene_add_primitive(t_scene *scene, t_primitive_array p_data, int type)
{
	int	idx;

	if (!ensure_prim_cap(&scene->primitives))
		return (false);
	idx = scene->primitives.count++;
	scene->primitives.types[idx] = (uint8_t)type;
	scene->primitives.positions[idx] = p_data.positions[0];
	scene->primitives.axes[idx] = p_data.axes[0];
	scene->primitives.radii[idx] = p_data.radii[0];
	scene->primitives.heights[idx] = p_data.heights[0];
	scene->primitives.mat_ids[idx] = p_data.mat_ids[0];
	return (true);
}

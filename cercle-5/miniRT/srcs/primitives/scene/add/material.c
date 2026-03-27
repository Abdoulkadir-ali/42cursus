/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 05:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 05:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Ensures material pool capacity.
 */
static bool	ensure_mat_cap(t_scene *scene)
{
	t_material	*new_mats;
	size_t		new_cap;

	if (scene->mat_count < scene->mat_cap)
		return (true);
	new_cap = scene->mat_cap;
	if (new_cap == 0)
		new_cap = 64;
	else
		new_cap *= 2;
	new_mats = ft_realloc(scene->materials, scene->mat_count * sizeof(t_material), 
				new_cap * sizeof(t_material));
	if (!new_mats)
		return (false);
	scene->materials = new_mats;
	scene->mat_cap = new_cap;
	return (true);
}

/**
 * @brief DOD optimized material injection.
 * Adds a new material to the scene pool and returns its index.
 */
int	scene_add_material(t_scene *scene, t_vec3 color)
{
	int			idx;
	t_material	*mat;

	if (!ensure_mat_cap(scene))
		return (-1);
	idx = (int)scene->mat_count++;
	mat = &scene->materials[idx];
	ft_memset(mat, 0, sizeof(t_material));
	mat->albedo_map.type = TEX_SOLID;
	mat->albedo_map.color_a = color;
	mat->albedo_map.scale = 1.0;
	mat->metallic = 0.0;
	mat->roughness = 1.0;
	mat->emission = vec3(0, 0, 0);
	mat->refract_index = 1.0;
	mat->transparency = 0.0;
	mat->reflectivity = 0.0;
	mat->specular = 0.5;
	mat->shininess = 32.0;
	return (idx);
}

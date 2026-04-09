/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:08:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"
#include "scene.h"
#include "utils.h"

size_t	scene_add_checker_material(t_scene *scene, t_vec3 color_a,
	t_vec3 color_b, double scale)
{
	if (scene_material_allocate_slot(scene).error)
		return (-1);
	ft_memset(&scene->materials[scene->mat_count - 1], 0, sizeof(t_material));
	scene->materials[scene->mat_count - 1].albedo_map.type = TEX_CHECKER;
	scene->materials[scene->mat_count - 1].albedo_map.color_a = color_a;
	scene->materials[scene->mat_count - 1].albedo_map.color_b = color_b;
	scene->materials[scene->mat_count - 1].albedo_map.scale = scale;
	scene->materials[scene->mat_count - 1].specular = 0.3;
	scene->materials[scene->mat_count - 1].shininess = 16.0;
	scene->materials[scene->mat_count - 1].em_intensity = 1.0;
	return (scene->mat_count - 1);
}

t_index	scene_add_material(t_scene *scene, t_vec3 color)
{
	size_t		i;
	t_material	*m;

	i = 0;
	while (i < scene->mat_count)
	{
		m = &scene->materials[i];
		if (m->albedo_map.type == TEX_SOLID
			&& vec3_compare(m->albedo_map.color_a, color)
			&& vec3_mag_sq(m->emission) == 0.0)
			return (init_index(i, false));
		i++;
	}
	return (scene_add_fresh_material(scene, color));
}

t_index	scene_add_named_material(t_scene *scene, const char *name)
{
	t_index	idx;

	idx = scene_material_allocate_slot(scene);
	if (idx.error)
		return (idx);
	ft_memset(&scene->materials[idx.i], 0, sizeof(t_material));
	scene->materials[idx.i].name = ft_strdup(name);
	scene->materials[idx.i].albedo_map.type = TEX_SOLID;
	scene->materials[idx.i].albedo_map.color_a = vec3(255, 255, 255);
	scene->materials[idx.i].albedo_map.scale = 1.0;
	scene->materials[idx.i].specular = 0.1;
	scene->materials[idx.i].shininess = 16.0;
	scene->materials[idx.i].em_intensity = 1.0;
	return (idx);
}

t_index	scene_add_fresh_material(t_scene *scene, t_vec3 color)
{
	t_material	*m;
	t_index		idx;

	idx = scene_material_allocate_slot(scene);
	if (idx.error)
		return (idx);
	m = &scene->materials[idx.i];
	ft_memset(m, 0, sizeof(t_material));
	m->albedo_map.type = TEX_SOLID;
	m->albedo_map.color_a = color;
	m->albedo_map.scale = 1.0;
	m->specular = 0.5;
	m->shininess = 32.0;
	m->em_intensity = 1.0;
	apply_magic_colors(m, color);
	apply_more_magic_colors(m, color);
	return (idx);
}

t_index	scene_find_material(t_scene *scene, const char *name)
{
	size_t	i;

	if (!name || !scene)
		return (init_index(0, true));
	i = 0;
	while (i < scene->mat_count)
	{
		if (scene->materials[i].name
			&& ft_strcmp(scene->materials[i].name, name) == 0)
			return (init_index(i, false));
		i++;
	}
	return (init_index(0, true));
}

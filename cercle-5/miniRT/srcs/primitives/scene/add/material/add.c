/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:27:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"
#include "scene.h"
#include "utils.h"


int	scene_add_checker_material(t_scene *scene, t_vec3 color_a,
	t_vec3 color_b, double scale)
{
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	ft_memset(&scene->materials[scene->mat_count], 0, sizeof(t_material));
	scene->materials[scene->mat_count].albedo_map.type = TEX_CHECKER;
	scene->materials[scene->mat_count].albedo_map.color_a = color_a;
	scene->materials[scene->mat_count].albedo_map.color_b = color_b;
	scene->materials[scene->mat_count].albedo_map.scale = scale;
	scene->materials[scene->mat_count].specular = 0.3;
	scene->materials[scene->mat_count].shininess = 16.0;
	return (scene->mat_count++);
}


int	scene_add_material(t_scene *scene, t_vec3 color)
{
	int			i;
	t_material	*m;

	i = 0;
	while (i < scene->mat_count)
	{
		m = &scene->materials[i];
		if (m->albedo_map.type == TEX_SOLID
			&& vec3_compare(m->albedo_map.color_a, color)
			&& vec3_mag_sq(m->emission) == 0.0)
			return (i);
		i++;
	}
	return (scene_add_fresh_material(scene, color));
}

int	scene_add_named_material(t_scene *scene, const char *name)
{
	int	id;

	id = scene_material_allocate_slot(scene);
	if (id < 0)
		return (-1);
	ft_memset(&scene->materials[id], 0, sizeof(t_material));
	scene->materials[id].name = ft_strdup(name);
	scene->materials[id].albedo_map.type = TEX_SOLID;
	scene->materials[id].albedo_map.color_a = vec3(255, 255, 255);
	scene->materials[id].albedo_map.scale = 1.0;
	scene->materials[id].specular = 0.1;
	scene->materials[id].shininess = 16.0;
	return (id);
}


int	scene_add_fresh_material(t_scene *scene, t_vec3 color)
{
	t_material	*m;

	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	m = &scene->materials[scene->mat_count];
	ft_memset(m, 0, sizeof(t_material));
	m->albedo_map.type = TEX_SOLID;
	m->albedo_map.color_a = color;
	m->albedo_map.scale = 1.0;
	m->albedo_map.specular = 0.5;
	m->albedo_map.shininess = 32.0;
	apply_magic_colors(m, color);
	apply_more_magic_colors(m, color);
	return (scene->mat_count++);
}


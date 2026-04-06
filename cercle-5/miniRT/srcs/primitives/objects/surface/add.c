/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:55:47 by abdoali          ###   ########.fr       */
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
	return (scene->mat_count - 1);
}

t_index	scene_add_material(t_scene *scene, t_vec3 color)
{
	size_t		i;
	t_material	*m;
	t_index		id;

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
	id = scene_add_fresh_material(scene, color);
	return (id);
}

t_index	scene_add_named_material(t_scene *scene, const char *name)
{
	t_index	id;

	id = scene_material_allocate_slot(scene);
	if (id.error)
		return (id);
	ft_memset(&scene->materials[id.i], 0, sizeof(t_material));
	scene->materials[id.i].name = ft_strdup(name);
	scene->materials[id.i].albedo_map.type = TEX_SOLID;
	scene->materials[id.i].albedo_map.color_a = vec3(255, 255, 255);
	scene->materials[id.i].albedo_map.scale = 1.0;
	scene->materials[id.i].specular = 0.1;
	scene->materials[id.i].shininess = 16.0;
	return (id);
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

static bool	mat_needs_uv(t_material *m)
{
	return (m->albedo_map.type != TEX_SOLID
		|| m->roughness_map.type != TEX_SOLID
		|| m->metallic_map.type != TEX_SOLID);
}

void	scene_init_uv_flags(t_scene *scene)
{
	size_t		i;
	t_material	*m;

	i = 0;
	while (i < scene->sphere_count)
	{
		m = &scene->materials[scene->spheres[i].mat_slots[
			scene->spheres[i].active_slot]];
		scene->spheres[i].needs_uv = mat_needs_uv(m);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		m = &scene->materials[scene->planes[i].mat_slots[
			scene->planes[i].active_slot]];
		scene->planes[i].needs_uv = mat_needs_uv(m);
		i++;
	}
}

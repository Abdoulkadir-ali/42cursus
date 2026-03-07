/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:15:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:15:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "scene.h"
#include "utils.h"

/*
** Adds a material to the scene.
** reused existing identical materials to save memory.
*/
int	scene_add_material(t_scene *scene, t_vec3 color)
{
	int			i;
	t_material	*m;

	i = 0;
	while (i < scene->mat_count)
	{
		m = &scene->materials[i];
		if (m->albedo_map.type == TEX_SOLID
			&& vec3_compare(m->albedo_map.color_a, color))
			return (i);
		i++;
	}
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	ft_memset(&scene->materials[scene->mat_count], 0, sizeof(t_material));
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a = color;
	scene->materials[scene->mat_count].albedo_map.scale = 1.0;
	scene->materials[scene->mat_count].specular = 0.5;
	scene->materials[scene->mat_count].shininess = 32.0;

	/* Magic Colors for Advanced Materials */
	if (color.x == 255 && color.y == 0 && color.z == 255) /* Magenta = Glass */
	{
		scene->materials[scene->mat_count].refract_index = 1.5;
		scene->materials[scene->mat_count].transparency = 0.9;
		scene->materials[scene->mat_count].reflectivity = 0.1;
		scene->materials[scene->mat_count].specular = 0.9;
		scene->materials[scene->mat_count].shininess = 128.0;
	}
	else if (color.x == 0 && color.y == 255 && color.z == 255) /* Cyan = Mirror */
	{
		scene->materials[scene->mat_count].reflectivity = 0.8;
		scene->materials[scene->mat_count].specular = 0.9;
		scene->materials[scene->mat_count].shininess = 256.0;
	}
	else if (color.x == 0 && color.y == 0 && color.z == 255) /* Blue = Water */
	{
		scene->materials[scene->mat_count].refract_index = 1.33;
		scene->materials[scene->mat_count].transparency = 0.8;
		scene->materials[scene->mat_count].reflectivity = 0.2;
		scene->materials[scene->mat_count].specular = 0.8;
		scene->materials[scene->mat_count].shininess = 64.0;
	}
	else if (color.x == 200 && color.y == 160 && color.z == 255) /* Lavender = Glass */
	{
		scene->materials[scene->mat_count].refract_index = 1.5;
		scene->materials[scene->mat_count].transparency = 0.7;
		scene->materials[scene->mat_count].reflectivity = 0.2;
		scene->materials[scene->mat_count].specular = 0.9;
		scene->materials[scene->mat_count].shininess = 128.0;
	}
	else if (color.x == 255 && color.y == 255 && color.z == 0) /* Yellow = Emissive */
	{
		scene->materials[scene->mat_count].emission = vec3(255, 255, 150);
		scene->materials[scene->mat_count].albedo_map.color_a
			= vec3(255, 255, 150);
		scene->materials[scene->mat_count].specular = 0.0;
		scene->materials[scene->mat_count].shininess = 1.0;
	}

	return (scene->mat_count++);
}

/*
** Finds a material by name.
** Returns -1 if not found.
*/
int	scene_find_material(t_scene *scene, const char *name)
{
	int	i;

	if (!name)
		return (-1);
	i = 0;
	while (i < scene->mat_count)
	{
		if (scene->materials[i].name
			&& ft_strcmp(scene->materials[i].name, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
** Adds a new named material.
*/
int	scene_add_named_material(t_scene *scene, const char *name)
{
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	ft_memset(&scene->materials[scene->mat_count], 0, sizeof(t_material));
	scene->materials[scene->mat_count].name = ft_strdup(name);
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a
		= vec3(255, 255, 255);
	scene->materials[scene->mat_count].albedo_map.scale = 1.0;
	scene->materials[scene->mat_count].specular = 0.1;
	scene->materials[scene->mat_count].shininess = 16.0;
	return (scene->mat_count++);
}

/*
** Creates a UE-style default checkerboard material (dark/light gray).
** Returns the material index, or -1 on failure.
*/
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "material.h"

/*
** Ensures that the array has enough capacity to add a new element.
** Resizes the array if necessary.
*/
static bool	ensure_capacity(void **array, int *count, int *cap, size_t elem_size)
{
	void	*tmp;
	int		new_cap;

	if (*count < *cap)
		return (true);
	if (*cap == 0)
		new_cap = 16;
	else
		new_cap = *cap * 2;
	tmp = realloc(*array, new_cap * elem_size);
	if (!tmp)
	{
		printf("Error: Memory allocation failed while resizing scene array\n");
		return (false);
	}
	*array = tmp;
	*cap = new_cap;
	return (true);
}

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
	if (!ensure_capacity((void **)&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	ft_memset(&scene->materials[scene->mat_count], 0, sizeof(t_material));
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a = color;
	scene->materials[scene->mat_count].albedo_map.scale = 1.0;
	scene->materials[scene->mat_count].specular = 0.5;
	scene->materials[scene->mat_count].shininess = 32.0;
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
		if (scene->materials[i].name && ft_strcmp(scene->materials[i].name, name) == 0)
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
	if (!ensure_capacity((void **)&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	ft_memset(&scene->materials[scene->mat_count], 0, sizeof(t_material));
	scene->materials[scene->mat_count].name = ft_strdup(name);
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a = vec3(255, 255, 255);
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
	if (!ensure_capacity((void **)&scene->materials, &scene->mat_count,
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

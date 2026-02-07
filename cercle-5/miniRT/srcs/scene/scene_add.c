/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 02:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 03:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h" // for ft_memset if needed
#include <stdlib.h>
#include <stdio.h> // for error printing

int	scene_add_material(t_scene *scene, t_vec3 color)
{
	t_material	*tmp;
	int			i;

	// Deduplication: Check if material already exists (Assume solid for now)
	for (i = 0; i < scene->mat_count; i++)
	{
		if (scene->materials[i].albedo_map.type == TEX_SOLID)
		{
			t_vec3 c = scene->materials[i].albedo_map.color_a;
			if (c.x == color.x && c.y == color.y && c.z == color.z)
				return (i);
		}
	}

	if (scene->mat_count >= scene->mat_cap)
	{
		scene->mat_cap *= 2;
		tmp = realloc(scene->materials, scene->mat_cap * sizeof(t_material));
		if (!tmp)
			return (-1); // Return -1 for error
		scene->materials = tmp;
	}
	
	// Add logic to check for duplicates?
	// For now simple append
	
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a = color;
	scene->materials[scene->mat_count].albedo_map.scale = 1.0;
	
	// Default material props
	scene->materials[scene->mat_count].specular = 0.5;
	scene->materials[scene->mat_count].shininess = 32.0;

	return (scene->mat_count++);
}


bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	t_sphere	*tmp;

	// Create unique material for this object using its temp_color
	int mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id < 0) return (false);
	sphere.mat_id = mat_id;

	if (scene->sphere_count >= scene->sphere_cap)
	{
		scene->sphere_cap *= 2;
		tmp = realloc(scene->spheres, scene->sphere_cap * sizeof(t_sphere));
		if (!tmp)
			return (false); // Handle error
		scene->spheres = tmp;
	}
	scene->spheres[scene->sphere_count++] = sphere;
	return (true);
}

bool	scene_add_plane(t_scene *scene, t_plane plane)
{
	t_plane	*tmp;

	int mat_id = scene_add_material(scene, plane.temp_color);
	if (mat_id < 0) return (false);
	plane.mat_id = mat_id;

	if (scene->plane_count >= scene->plane_cap)
	{
		scene->plane_cap *= 2;
		tmp = realloc(scene->planes, scene->plane_cap * sizeof(t_plane));
		if (!tmp)
			return (false);
		scene->planes = tmp;
	}
	scene->planes[scene->plane_count++] = plane;
	return (true);
}

bool	scene_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	*tmp;

	int mat_id = scene_add_material(scene, cylinder.temp_color);
	if (mat_id < 0) return (false);
	cylinder.mat_id = mat_id;

	if (scene->cylinder_count >= scene->cylinder_cap)
	{
		scene->cylinder_cap *= 2;
		tmp = realloc(scene->cylinders, scene->cylinder_cap * sizeof(t_cylinder));
		if (!tmp)
			return (false);
		scene->cylinders = tmp;
	}
	scene->cylinders[scene->cylinder_count++] = cylinder;
	return (true);
}

bool	scene_add_cone(t_scene *scene, t_cone cone)
{
	t_cone	*tmp;

	int mat_id = scene_add_material(scene, cone.temp_color);
	if (mat_id < 0) return (false);
	cone.mat_id = mat_id;

	if (scene->cone_count >= scene->cone_cap)
	{
		scene->cone_cap *= 2;
		tmp = realloc(scene->cones, scene->cone_cap * sizeof(t_cone));
		if (!tmp)
			return (false);
		scene->cones = tmp;
	}
	scene->cones[scene->cone_count++] = cone;
	return (true);
}

bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	t_mesh	*tmp;

	if (scene->mesh_count >= scene->mesh_cap)
	{
		scene->mesh_cap *= 2;
		tmp = realloc(scene->meshes, scene->mesh_cap * sizeof(t_mesh));
		if (!tmp)
			return (false);
		scene->meshes = tmp;
	}
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}

bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	t_skinned_mesh	*tmp;

	if (scene->anim_count >= scene->anim_cap)
	{
		scene->anim_cap *= 2;
		tmp = realloc(scene->animated, scene->anim_cap * sizeof(t_skinned_mesh));
		if (!tmp)
			return (false);
		scene->animated = tmp;
	}
	scene->animated[scene->anim_count++] = animated;
	return (true);
}

bool	scene_add_light(t_scene *scene, t_light light)
{
	t_light	*tmp;

	if (scene->light_count >= scene->light_cap)
	{
		scene->light_cap *= 2;
		tmp = realloc(scene->lights, scene->light_cap * sizeof(t_light));
		if (!tmp)
			return (false);
		scene->lights = tmp;
	}
	scene->lights[scene->light_count++] = light;
	return (true);
}

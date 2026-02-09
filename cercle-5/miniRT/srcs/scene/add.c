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
		return (false);
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
	scene->materials[scene->mat_count].albedo_map.type = TEX_SOLID;
	scene->materials[scene->mat_count].albedo_map.color_a = color;
	scene->materials[scene->mat_count].albedo_map.scale = 1.0;
	scene->materials[scene->mat_count].specular = 0.5;
	scene->materials[scene->mat_count].shininess = 32.0;
	return (scene->mat_count++);
}

/*
** Adds a sphere to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	int	mat_id;

	mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id < 0)
		return (false);
	sphere.mat_id = mat_id;
	if (!ensure_capacity((void **)&scene->spheres, &scene->sphere_count,
			&scene->sphere_cap, sizeof(t_sphere)))
		return (false);
	scene->spheres[scene->sphere_count++] = sphere;
	return (true);
}

/*
** Adds a plane to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_plane(t_scene *scene, t_plane plane)
{
	int	mat_id;

	mat_id = scene_add_material(scene, plane.temp_color);
	if (mat_id < 0)
		return (false);
	plane.mat_id = mat_id;
	if (!ensure_capacity((void **)&scene->planes, &scene->plane_count,
			&scene->plane_cap, sizeof(t_plane)))
		return (false);
	scene->planes[scene->plane_count++] = plane;
	return (true);
}

/*
** Adds a cylinder to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cylinder.temp_color);
	if (mat_id < 0)
		return (false);
	cylinder.mat_id = mat_id;
	if (!ensure_capacity((void **)&scene->cylinders, &scene->cylinder_count,
			&scene->cylinder_cap, sizeof(t_cylinder)))
		return (false);
	scene->cylinders[scene->cylinder_count++] = cylinder;
	return (true);
}

/*
** Adds a cone to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cone(t_scene *scene, t_cone cone)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cone.temp_color);
	if (mat_id < 0)
		return (false);
	cone.mat_id = mat_id;
	if (!ensure_capacity((void **)&scene->cones, &scene->cone_count,
			&scene->cone_cap, sizeof(t_cone)))
		return (false);
	scene->cones[scene->cone_count++] = cone;
	return (true);
}

/*
** Adds a mesh to the scene.
*/
bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	if (!ensure_capacity((void **)&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}

/*
** Adds an animated mesh to the scene.
*/
bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
	if (!ensure_capacity((void **)&scene->animated, &scene->anim_count,
			&scene->anim_cap, sizeof(t_skinned_mesh)))
		return (false);
	scene->animated[scene->anim_count++] = animated;
	return (true);
}

/*
** Adds a light to the scene.
*/
bool	scene_add_light(t_scene *scene, t_light light)
{
	if (!ensure_capacity((void **)&scene->lights, &scene->light_count,
			&scene->light_cap, sizeof(t_light)))
		return (false);
	scene->lights[scene->light_count++] = light;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:06:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mesh.h"

/**
 * Bridges a standalone t_mesh_resource into the global t_scene world state.
 * Transfers ownership of meshes, groups, and materials.
 */
bool	scene_integrate_resource(t_scene *scene, t_mesh_resource *res)
{
	int	i;
	int	base_mat;

	i = 0;
	base_mat = scene->mat_count;
	// 1. Integrate Materials
	while (i < res->mat_count)
	{
		scene_add_named_material(scene, res->materials[i].name);
		scene->materials[scene->mat_count - 1] = res->materials[i];
		i++;
	}
	// 2. Integrate Meshes (remap material IDs)
	i = 0;
	while (i < res->mesh_count)
	{
		res->meshes[i].mat_id += base_mat;
		scene_add_mesh(scene, res->meshes[i]);
		i++;
	}
	// 3. Integrate Groups
	i = 0;
	while (i < res->group_count)
	{
		scene_add_group(scene, res->groups[i]);
		i++;
	}
	// Clear the resource container but don't free the internal data 
	// (ownership moved to scene)
	ft_memset(res, 0, sizeof(t_mesh_resource));
	return (true);
}

/**
 * Unified loader that coordinates the new pure factory loaders with the scene.
 */
bool	scene_load_asset(t_scene *scene, const char *path,
			bool (*parser)(const char *, t_mesh_resource *, void *))
{
	t_mesh_resource	res;
	bool			status;

	mesh_resource_init(&res);
	status = parser(path, &res, scene->mlx);
	if (status)
		scene_integrate_resource(scene, &res);
	else
		mesh_resource_free(&res);
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:07:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "dispatcher.h"

static void	clone_instance_materials(t_scene *scene, int start_mesh)
{
	int	i;
	int	new_id;

	i = start_mesh;
	while (i < scene->mesh_count)
	{
		new_id = scene_clone_material(scene, scene->meshes[i].mat_id);
		if (new_id >= 0)
			scene->meshes[i].mat_id = new_id;
		i++;
	}
}

static void	apply_material(t_parse_obj *item, t_scene *scene, int start_mesh)
{
	int	i;

	i = start_mesh;
	while (i < scene->mesh_count)
	{
		scene->materials[scene->meshes[i].mat_id].albedo_map.color_a
			= item->data.mesh_info.color;
		i++;
	}
}

/**
 * High-level orchestration for injecting mesh resources into the scene.
 * This is the ONLY domain logically allowed to know about both the
 * isolated asset (t_mesh_resource) and the global world state (t_scene).
 */
static bool	inject_mesh_resource(t_scene *scene, t_mesh_resource *res)
{
	int	mi;
	int	gi;

	mi = 0;
	while (mi < res->mesh_count)
	{
		if (!scene_add_mesh(scene, res->meshes[mi]))
			return (false);
		mi++;
	}
	gi = 0;
	while (gi < res->group_count)
	{
		if (!scene_add_group(scene, res->groups[gi]))
			return (false);
		gi++;
	}
	return (true);
}

bool	scene_add_collection(t_scene *scene, t_parse_obj *item)
{
	t_mesh_resource	res;
	int				start_mesh;

	start_mesh = scene->mesh_count;
	if (mesh_cache_has(scene, item->data.mesh_info.path))
	{
		if (!mesh_cache_restore(scene, item->data.mesh_info.path))
			return (false);
	}
	else
	{
		if (!mesh_build_resource(item->data.mesh_info.path, &res))
			return (false);
		if (!inject_mesh_resource(scene, &res))
			return (false);
		mesh_cache_save(scene, item->data.mesh_info.path, start_mesh);
		clone_instance_materials(scene, start_mesh);
	}
	apply_material(item, scene, start_mesh);
	if (scene->mesh_count > start_mesh)
		scene_add_group_for_subs(scene, item->data.mesh_info.path, start_mesh);
	return (true);
}

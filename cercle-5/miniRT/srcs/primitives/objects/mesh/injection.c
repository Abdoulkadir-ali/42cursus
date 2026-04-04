/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:34:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "dispatcher.h"

static void	clone_instance_materials(t_scene *scene, size_t start_mesh)
{
	size_t	i;
	t_index	new_id;

	i = start_mesh;
	while (i < scene->mesh_count)
	{
		new_id = scene_clone_material(scene, scene->meshes[i].mat_id);
		if (!new_id.error)
			scene->meshes[i].mat_id = new_id.i;
		i++;
	}
}

static void	apply_instance_material(t_scene *scene, size_t start_mesh, t_vec3 col)
{
	size_t	i;

	i = start_mesh;
	while (i < scene->mesh_count)
	{
		scene->materials[scene->meshes[i].mat_id].albedo_map.color_a = col;
		i++;
	}
}

bool	scene_inject_mesh_resource(t_scene *scene, t_mesh_resource *res,
			t_mesh_info *info)
{
	size_t	mi;
	size_t	gi;
	size_t	start_mesh;

	start_mesh = scene->mesh_count;
	if (mesh_cache_has(scene, info->path))
	{
		mesh_resource_free(res);
		return (mesh_cache_restore(scene, info->path));
	}
	mi = 0;
	while (mi < res->mat_count)
	{
		scene_material_allocate_slot(scene);
		scene->materials[scene->mat_count - 1] = res->materials[mi];
		mi++;
	}
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
	mesh_cache_save(scene, info->path, start_mesh);
	clone_instance_materials(scene, start_mesh);
	apply_instance_material(scene, start_mesh, info->color);
	if (scene->mesh_count > start_mesh)
		scene_add_group_for_subs(scene, info->path, start_mesh);
	return (true);
}

bool	scene_add_collection(t_scene *scene, t_parse_obj *item)
{
	t_mesh_resource	res;

	if (mesh_cache_has(scene, item->data.mesh_info.path))
		return (mesh_cache_restore(scene, item->data.mesh_info.path));
	if (!mesh_build_resource(scene->pool, item->data.mesh_info.path, &res))
		return (false);
	return (scene_inject_mesh_resource(scene, &res, &item->data.mesh_info));
}

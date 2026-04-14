/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 02:19:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mesh.h"

static void	apply_instance_mods(t_scene *scene, size_t start, t_mesh_info *info)
{
	size_t		i;
	t_index		new_id;
	t_transform	tf;

	tf = info->transform;
	if (vec3_mag_sq(tf.scale) < 1e-6)
		tf.scale = vec3(1, 1, 1);
	i = start;
	while (i < scene->mesh_count)
	{
		mesh_apply_transform(&scene->meshes[i], tf);
		new_id = scene_clone_material(scene, scene->meshes[i].mat_id);
		if (!new_id.error)
		{
			scene->meshes[i].mat_id = new_id.i;
			scene->meshes[i].mat_slots[0] = new_id.i;
		}
		scene->materials[scene->meshes[i].mat_id].albedo_map.color_a
			= info->color;
		if (!(vec3_mag_sq(info->emission) < 1e-6))
			scene->materials[scene->meshes[i].mat_id].emission = info->emission;
		i++;
	}
}

static void	inject_res_items(t_scene *scene, t_mesh_resource *res)
{
	size_t	i;
	size_t	mat_offset;

	mat_offset = scene->mat_count;
	i = 0;
	while (i < res->mat_count)
	{
		scene_material_allocate_slot(scene);
		scene->materials[scene->mat_count - 1] = res->materials[i++];
	}
	i = 0;
	while (i < res->mesh_count)
	{
		if (mat_offset > 0)
			res->meshes[i].mat_id += mat_offset;
		scene_add_mesh(scene, res->meshes[i++]);
	}
	i = 0;
	while (i < res->group_count)
		scene_add_group(scene, res->groups[i++]);
}

bool	scene_inject_mesh_resource(t_scene *scene, t_mesh_resource *res,
			t_mesh_info *info)
{
	size_t	start_mesh;

	start_mesh = scene->mesh_count;
	if (mesh_cache_has(scene, info->path))
	{
		mesh_resource_free(res);
		return (mesh_cache_restore(scene, info->path));
	}
	inject_res_items(scene, res);
	mesh_cache_save(scene, info->path, start_mesh);
	apply_instance_mods(scene, start_mesh, info);
	if (scene->mesh_count > start_mesh)
		scene_add_group_for_subs(scene, info->path, start_mesh);
	return (true);
}

/*
** Like scene_inject_mesh_resource but never checks or writes the cache.
** Used by soft bodies so each instance gets its own independent mesh copy.
*/
bool	scene_inject_mesh_resource_unique(t_scene *scene, t_mesh_resource *res,
			t_mesh_info *info)
{
	size_t	start_mesh;

	start_mesh = scene->mesh_count;
	inject_res_items(scene, res);
	apply_instance_mods(scene, start_mesh, info);
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

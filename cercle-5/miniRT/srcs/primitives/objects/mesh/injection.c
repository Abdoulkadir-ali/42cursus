/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 22:34:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mesh.h"

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

static void	apply_instance_emission(t_scene *scene, size_t start_mesh, t_vec3 em)
{
	size_t	i;

	if (em.x == 0.0 && em.y == 0.0 && em.z == 0.0)
		return ;
	i = start_mesh;
	while (i < scene->mesh_count)
	{
		scene->materials[scene->meshes[i].mat_id].emission = em;
		i++;
	}
}

static void	apply_instance_transform(t_scene *scene, size_t start, t_transform tf)
{
	size_t	i;

	if (vec3_mag_sq(tf.scale) < 1e-6)
		tf.scale = vec3(1, 1, 1);
	i = start;
	while (i < scene->mesh_count)
	{
		mesh_apply_transform(&scene->meshes[i], tf);
		i++;
	}
}

bool	scene_inject_mesh_resource(t_scene *scene, t_mesh_resource *res,
			t_mesh_info *info)
{
	size_t	i;
	size_t	start_mesh;

	ft_print_debug("INJECT: %s (res meshes=%zu)\n", info->path, res->mesh_count);
	start_mesh = scene->mesh_count;
	if (mesh_cache_has(scene, info->path))
	{
		mesh_resource_free(res);
		return (mesh_cache_restore(scene, info->path));
	}
	i = 0;
	while (i < res->mat_count)
	{
		scene_material_allocate_slot(scene);
		scene->materials[scene->mat_count - 1] = res->materials[i];
		i++;
	}
	i = 0;
	while (i < res->mesh_count)
	{
		if (!scene_add_mesh(scene, res->meshes[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < res->group_count)
	{
		if (!scene_add_group(scene, res->groups[i]))
			return (false);
		i++;
	}
	mesh_cache_save(scene, info->path, start_mesh);
	clone_instance_materials(scene, start_mesh);
	apply_instance_transform(scene, start_mesh, info->transform);
	apply_instance_material(scene, start_mesh, info->color);
	apply_instance_emission(scene, start_mesh, info->emission);
	if (scene->mesh_count > start_mesh)
		scene_add_group_for_subs(scene, info->path, start_mesh);
	ft_print_debug("INJECT: done, total meshes=%zu\n", scene->mesh_count);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:02:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 17:03:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for injecting an object file into a scene during RT parsing.
 * Now it is oblivious to the transformation/material logic.
 */
bool	handle_mesh_injection_internal(t_scene *scene, t_mesh_info *info, t_type type)
{
	int		start_tri;

	(void)type;
	start_tri = scene->tri_count;
	if (mesh_cache_has(info->path))
	{
		if (!mesh_cache_restore(info->path, scene))
			return (false);
	}
	else
	{
		/* Scene-aware injected load: loader should add triangles directly. */
		if (!load_injected_mesh(scene, info->path, info->transform,
						info->color, info->emission))
			return (false);
		mesh_cache_save(info->path, scene, start_tri);
	}
	if (scene->tri_count > start_tri)
		scene_add_group_for_subs(scene, info->path, start_tri);
	free(info->path);
	return (true);
}

bool	loader_convert_raw_model_to_scene(t_scene *scene, t_raw_model *model)
{
	int *mat_ids;
	int i;

	mat_ids = ft_calloc(model->mat_count, sizeof(int));
	if (!mat_ids && model->mat_count > 0)
		return (false);
	i = -1;
	while (++i < model->mat_count)
	{
		mat_ids[i] = scene_add_named_material(scene, model->materials[i].name);
		if (mat_ids[i] >= 0)
		{
			scene->materials[mat_ids[i]].albedo_map.color_a = model->materials[i].color;
			scene->materials[mat_ids[i]].specular = model->materials[i].specular;
			scene->materials[mat_ids[i]].roughness = model->materials[i].roughness;
			if (model->materials[i].has_tex)
			{
				if (model->materials[i].tex_data)
					load_texture_from_memory(&scene->materials[mat_ids[i]].albedo_map,
						model->materials[i].tex_data, model->materials[i].tex_len);
				else if (model->materials[i].albedo_map_path[0])
					load_texture(scene, &scene->materials[mat_ids[i]].albedo_map,
						model->materials[i].albedo_map_path);
			}
		}
	}
	i = -1;
	while (++i < model->mesh_count)
	{
		if (model->mesh_mat_indices)
		{
			int midx = model->mesh_mat_indices[i];
			if (midx >= 0 && midx < model->mat_count)
				model->meshes[i].mat_id = mat_ids[midx];
		}
		scene_add_mesh(scene, model->meshes[i]);
	}
	i = -1;
	while (++i < model->anim_count)
		scene_add_animation(scene, model->anims[i]);
	free(mat_ids);
	return (true);
}

bool	scene_add_glb(t_scene *scene, t_glb_model model)
{
	int *mat_ids;
	int i;

	mat_ids = ft_calloc(model.mat_count, sizeof(int));
	if (!mat_ids && model.mat_count > 0)
		return (false);
	i = -1;
	while (++i < model.mat_count)
	{
		mat_ids[i] = scene_add_named_material(scene, model.materials[i].name);
		if (mat_ids[i] >= 0)
		{
			scene->materials[mat_ids[i]].albedo_map = model.materials[i].albedo_map;
			scene->materials[mat_ids[i]].specular = model.materials[i].specular;
			scene->materials[mat_ids[i]].roughness = model.materials[i].roughness;
		}
	}
	i = -1;
	while (++i < model.mesh_count)
	{
		if (model.meshes[i].mat_id >= 0 && model.meshes[i].mat_id < model.mat_count)
			model.meshes[i].mat_id = mat_ids[model.meshes[i].mat_id];
		scene_add_mesh(scene, model.meshes[i]);
	}
	i = -1;
	while (++i < model.anim_count)
		scene_add_animation(scene, model.anims[i]);
	free(mat_ids);
	return (true);
}

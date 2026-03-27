/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 12:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

static int	load_raw_materials(t_scene *scene, t_raw_model model, int **out_mat_ids)
{
	int	*mat_ids;
	int	i;

	mat_ids = ft_calloc(model.mat_count, sizeof(int));
	if (!mat_ids)
		return (-1);
	i = -1;
	while (++i < model.mat_count)
	{
		mat_ids[i] = scene_add_named_material(scene, model.materials[i].name);
		if (mat_ids[i] >= 0)
		{
			scene->materials[mat_ids[i]].albedo_map.color_a = model.materials[i].color;
			scene->materials[mat_ids[i]].specular = model.materials[i].specular;
			scene->materials[mat_ids[i]].roughness = model.materials[i].roughness;
			if (model.materials[i].has_tex)
			{
				if (model.materials[i].tex_data)
					load_texture_from_memory(&scene->materials[mat_ids[i]].albedo_map,
						model.materials[i].tex_data, model.materials[i].tex_len);
				else if (model.materials[i].albedo_map_path[0])
					load_texture(scene, &scene->materials[mat_ids[i]].albedo_map,
						model.materials[i].albedo_map_path);
			}
		}
	}
	*out_mat_ids = mat_ids;
	return (0);
}

bool	scene_add_raw_model(t_scene *scene, t_raw_model model)
{
	int	*mat_ids;
	int	anim_base;
	int	i;

	anim_base = scene->anim_count;
	if (load_raw_materials(scene, model, &mat_ids) < 0)
		return (false);
	i = -1;
	while (++i < model.mesh_count)
	{
		if (model.mesh_mat_indices)
		{
			int mat_idx = model.mesh_mat_indices[i];
			if (mat_idx >= 0 && mat_idx < model.mat_count)
				model.meshes[i].mat_id = mat_ids[mat_idx];
		}
		scene_add_mesh(scene, model.meshes[i]);
	}
	
	/* 3. Add animations */
	i = -1;
	while (++i < model.anim_count)
		scene_add_animation(scene, model.anims[i]);
	
	free(mat_ids);
	return (true);
}

bool	scene_add_animation(t_scene *scene, t_animation anim)
{
	if (!DYNARRAY_ENSURE_INT(&scene->clips, &scene->clip_count,
			&scene->clip_cap, sizeof(t_animation)))
		return (false);
	scene->clips[scene->clip_count++] = anim;
	return (true);
}

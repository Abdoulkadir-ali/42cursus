/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_injection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	parse_mesh_file(t_parse_obj *obj, const char *ext, t_scene *scene)
{
	if (!validate_file(obj->data.mesh_info.path))
	{
		fprintf(stderr, "Error: File not found or invalid: %s\n",
			obj->data.mesh_info.path);
		return (false);
	}
	if (ext && ft_strcmp(ext, ".fbx") == 0)
		return (parse_fbx(obj->data.mesh_info.path, scene));
	if (ext && ft_strcmp(ext, ".obj") == 0)
		return (parse_obj(obj->data.mesh_info.path, scene));
	if (ext && ft_strcmp(ext, ".fdf") == 0)
		return (parse_fdf(obj->data.mesh_info.path, scene));
	if (ext && ft_strcmp(ext, ".glb") == 0)
		return (parse_glb(obj->data.mesh_info.path, scene));
	return (false);
}

static void	apply_anim_material(t_scene *scene, t_parse_obj *obj, int mat_id, bool force, int start_idx)
{
	t_skinned_mesh	*anim;
	int				i;

	i = start_idx;
	while (i < scene->anim_count)
	{
		anim = &scene->animated[i];
		anim->base.transform = obj->data.mesh_info.transform;
		mesh_apply_transform(&anim->base, anim->base.transform);
		if (force || anim->base.mat_id <= 0
			|| scene->materials[anim->base.mat_id].albedo_map.type == TEX_SOLID)
			anim->base.mat_id = mat_id;
		i++;
	}
}

static void	apply_mesh_material(t_scene *scene, t_parse_obj *obj, int mat_id, bool force, int start_idx)
{
	t_mesh	*mesh;
	int		i;

	i = start_idx;
	while (i < scene->mesh_count)
	{
		mesh = &scene->meshes[i];
		mesh->transform = obj->data.mesh_info.transform;
		mesh_apply_transform(mesh, mesh->transform);
		if (force || scene->materials[mesh->mat_id].albedo_map.type != TEX_BITMAP)
			mesh->mat_id = mat_id;
		i++;
	}
}

static void	apply_material(t_parse_obj *obj, t_scene *scene,
		int start_mesh, int start_anim)
{
	int		mat_id;
	bool	force;

	force = false;
	mat_id = scene_add_fresh_material(scene, obj->data.mesh_info.color);
	if (vec3_mag_sq(obj->data.mesh_info.emission) > 0.0)
	{
		scene->materials[mat_id].emission = obj->data.mesh_info.emission;
		force = true;
	}
	if (obj->type == TYPE_ANIM && scene->anim_count > start_anim)
		apply_anim_material(scene, obj, mat_id, force, start_anim);
	else if (obj->type == TYPE_MESH && scene->mesh_count > start_mesh)
		apply_mesh_material(scene, obj, mat_id, force, start_mesh);
}

bool	handle_mesh_injection(t_parse_obj *obj, const char *ext, t_scene *scene)
{
	int		start_anim;
	int		start_mesh;

	start_anim = scene->anim_count;
	start_mesh = scene->mesh_count;
	if (mesh_cache_has(obj->data.mesh_info.path))
	{
		if (!mesh_cache_restore(obj->data.mesh_info.path, scene))
			return (false);
	}
	else
	{
		if (!parse_mesh_file(obj, ext, scene))
		{
			fprintf(stderr, "Error: Failed to parse %s\n",
				obj->data.mesh_info.path);
			return (false);
		}
		mesh_cache_save(obj->data.mesh_info.path, scene, start_mesh);
	}
	apply_material(obj, scene, start_mesh, start_anim);
	return (true);
}

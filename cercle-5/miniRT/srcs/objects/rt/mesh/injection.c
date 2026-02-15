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

static void	apply_anim_material(t_scene *scene, t_parse_obj *obj, int mat_id)
{
	t_skinned_mesh	*anim;

	anim = &scene->animated[scene->anim_count - 1];
	anim->base.transform = obj->data.mesh_info.transform;
	mesh_apply_transform(&anim->base, anim->base.transform);
	if (anim->base.mat_id <= 0
		|| scene->materials[anim->base.mat_id].albedo_map.type == TEX_SOLID)
		anim->base.mat_id = mat_id;
}

static void	apply_mesh_material(t_scene *scene, t_parse_obj *obj, int mat_id)
{
	t_mesh	*mesh;

	mesh = &scene->meshes[scene->mesh_count - 1];
	mesh->transform = obj->data.mesh_info.transform;
	mesh_apply_transform(mesh, mesh->transform);
	if (scene->materials[mesh->mat_id].albedo_map.type != TEX_BITMAP)
		mesh->mat_id = mat_id;
}

bool	handle_mesh_injection(t_parse_obj *obj, const char *ext, t_scene *scene)
{
	int	mat_id;

	if (!parse_mesh_file(obj, ext, scene))
	{
		fprintf(stderr, "Error: Failed to parse %s\n",
			obj->data.mesh_info.path);
		return (false);
	}
	mat_id = scene_add_material(scene, obj->data.mesh_info.color);
	if (obj->type == TYPE_ANIM && scene->anim_count > 0)
		apply_anim_material(scene, obj, mat_id);
	else if (obj->type == TYPE_MESH && scene->mesh_count > 0)
		apply_mesh_material(scene, obj, mat_id);
	return (true);
}

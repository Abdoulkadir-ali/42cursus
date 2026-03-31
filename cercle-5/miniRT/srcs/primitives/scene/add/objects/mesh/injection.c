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

bool	scene_add_collection(t_scene *scene, t_parse_obj *item, const char *ext)
{
	t_mesh_resource	res;
	int				start_anim;
	int				start_mesh;

	start_anim = scene->anim_count;
	start_mesh = scene->mesh_count;
	if (mesh_cache_has(scene, item->data.mesh_info.path))
	{
		if (!mesh_cache_restore(scene, item->data.mesh_info.path))
			return (false);
	}
	else
	{
		if (!mesh_build_resource(item->data.mesh_info.path, ext, &res))
			return (false);
		if (!inject_mesh_resource(scene, &res))
			return (false);
		mesh_cache_save(scene, item->data.mesh_info.path, start_mesh);
		clone_instance_materials(scene, start_mesh);
	}
	apply_material(item, scene, start_mesh, start_anim);
	if (scene->mesh_count > start_mesh)
		mesh_form_group_for_subs(scene, item->data.mesh_info.path, start_mesh);
	return (true);
}

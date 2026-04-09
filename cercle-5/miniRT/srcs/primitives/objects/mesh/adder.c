/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:07:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	process_mats_meshes(t_scene *scene, t_mesh_resource *res,
				size_t mat_offset)
{
	size_t	i;

	i = 0;
	while (i < res->mat_count)
	{
		if (scene_material_allocate_slot(scene).error)
			return (false);
		scene->materials[scene->mat_count - 1] = res->materials[i++];
	}
	i = 0;
	while (i < res->mesh_count)
	{
		if (mat_offset > 0)
			res->meshes[i].mat_id += mat_offset;
		if (!scene_add_mesh(scene, res->meshes[i++]))
			return (false);
	}
	return (true);
}

static bool	process_resource_items(t_scene *scene, t_mesh_resource *res)
{
	size_t	i;

	if (!process_mats_meshes(scene, res, scene->mat_count))
		return (false);
	i = 0;
	while (i < res->anim_count)
		if (!scene_add_animated(scene, res->animated[i++]))
			return (false);
	i = 0;
	while (i < res->group_count)
		if (!scene_add_group(scene, res->groups[i++]))
			return (false);
	if (res->clip_count > 0)
	{
		glb_ensure_clip_capacity(scene, res->clip_count);
		ft_memcpy(&scene->clips[scene->clip_count], res->clips,
			res->clip_count * sizeof(t_animation));
		scene->clip_count += res->clip_count;
	}
	return (true);
}

bool	scene_add_objects(t_scene *scene, const char *path)
{
	t_mesh_resource	res;
	size_t			start;

	if (!scene || !path)
		return (false);
	if (!mesh_build_resource(scene->pool, path, &res))
		return (false);
	start = scene->mesh_count;
	if (!process_resource_items(scene, &res))
		return (false);
	if (scene->mesh_count > start)
		scene_add_group_for_subs(scene, path, start);
	return (true);
}

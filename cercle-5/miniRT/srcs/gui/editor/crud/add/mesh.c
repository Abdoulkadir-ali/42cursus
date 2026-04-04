/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 10:00:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	glb_post_process(t_gui *gui, size_t mesh_start, const char *path)
{
	size_t	i;
	t_index	new_id;

	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		gui->scene->meshes[i].transform = (t_transform){0};
		gui->scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		new_id = scene_clone_material(gui->scene, gui->scene->meshes[i].mat_id);
		if (!new_id.error)
			gui->scene->meshes[i].mat_id = new_id.i;
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
	{
		scene_add_group_for_subs(gui->scene, path, mesh_start);
		select_object(gui, TYPE_MESH, gui->scene->group_count - 1);
	}
}

static void	glb_load_logic(t_gui *gui, size_t mesh_start, const char *path)
{
	size_t	i;

	if (mesh_cache_has(gui->scene, path))
	{
		if (!mesh_cache_restore(gui->scene, path))
			return ;
		i = mesh_start;
		while (i < gui->scene->mesh_count)
			gui->scene->meshes[i++].group_id = gui->scene->group_count;
		gui->scene->group_count++;
	}
	else
	{
		if (!parse_glb_worker(path, gui->scene))
			return ;
		mesh_cache_save(gui->scene, path, mesh_start);
	}
}

void	editor_add_obj(t_gui *gui, const char *path)
{
	size_t	mesh_start;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (!scene_parse_obj_worker(path, gui->scene))
		return ;
	glb_post_process(gui, mesh_start, path);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_glb(t_gui *gui, const char *path)
{
	size_t	mesh_start;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	glb_load_logic(gui, mesh_start, path);
	glb_post_process(gui, mesh_start, path);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

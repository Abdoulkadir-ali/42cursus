/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:07:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

void	editor_add_obj(t_gui *gui, const char *path)
{
	int		mesh_start;
	int		i;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (!parse_obj(path, gui->scene))
		return ;
	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
	{
		scene_add_group_for_subs(gui->scene, path, mesh_start);
		select_object(gui, TYPE_MESH, gui->scene->group_count - 1);
	}
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

void	editor_add_glb(t_gui *gui, const char *path)
{
	int		mesh_start;
	int		i;
	int		new_id;
	int		gid;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (mesh_cache_has(gui->scene, path))
	{
		if (!mesh_cache_restore(gui->scene, path))
			return ;
		gid = gui->scene->mesh_group_count++;
		i = mesh_start;
		while (i < gui->scene->mesh_count)
			gui->scene->meshes[i++].group_id = gid;
	}
	else
	{
		if (!parse_glb(path, gui->scene))
			return ;
		mesh_cache_save(gui->scene, path, mesh_start);
	}
	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		gui->scene->meshes[i].transform = (t_transform){0};
		gui->scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		new_id = scene_clone_material(gui->scene,
			gui->scene->meshes[i].mat_id);
		if (new_id >= 0)
			gui->scene->meshes[i].mat_id = new_id;
		i++;
	}
	if (gui->scene->mesh_count > mesh_start)
	{
		scene_add_group_for_subs(gui->scene, path, mesh_start);
		select_object(gui, TYPE_MESH, gui->scene->group_count - 1);
	}
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:53:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	post_process_meshes(t_gui *gui, int mesh_start)
{
	int	i;
	int	new_id;

	i = mesh_start;
	while (i < gui->scene->mesh_count)
	{
		gui->scene->meshes[i].transform = (t_transform){0};
		gui->scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&gui->scene->meshes[i],
			gui->scene->meshes[i].transform);
		new_id = scene_clone_material(gui->scene, gui->scene->meshes[i].mat_id);
		if (new_id >= 0)
			gui->scene->meshes[i].mat_id = new_id;
		i++;
	}
}

void	editor_add_glb(t_gui *gui, const char *path)
{
	int	mesh_start;
	int	i;
	int	new_id;
	int	gid;

	if (!gui->scene)
		return ;
	mesh_start = gui->scene->mesh_count;
	if (mesh_cache_has(path))
	{
		if (!mesh_cache_restore(path, gui->scene))
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
		mesh_cache_save(path, gui->scene, mesh_start);
	}
	post_process_meshes(gui, mesh_start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:51:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	editor_add_obj(t_gui *gui, const char *path)
{
	int	mesh_start;
	int	i;

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

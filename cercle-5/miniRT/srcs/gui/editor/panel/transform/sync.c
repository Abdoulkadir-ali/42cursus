/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:46:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "render.h"

void	transform_selection_sync(t_gui *gui)
{
	t_cmd	cmd;

	ft_memset(&cmd, 0, sizeof(cmd));
	if (gui->selection.type == TYPE_SPHERE)
	{
		sphere_scale_sync(gui);
		cmd.type = CMD_SET_POS;
		cmd.data.transform.obj_type = TYPE_SPHERE;
		cmd.data.transform.index = gui->selection.index;
		cmd.data.transform.pos = gui->transform.pos;
		cmd.data.transform.scale = gui->transform.scale;
		cmd_enqueue(gui, cmd);
	}
	else if (gui->selection.type == TYPE_PLANE)
	{
		cmd.type = CMD_SET_POS;
		cmd.data.transform.obj_type = TYPE_PLANE;
		cmd.data.transform.index = gui->selection.index;
		cmd.data.transform.pos = gui->transform.pos;
		cmd.data.transform.rot = gui->transform.rotation;
		cmd_enqueue(gui, cmd);
	}
	else if (gui->selection.type == TYPE_MESH)
		return ;
	else if (gui->selection.type == TYPE_LIGHT)
	{
		cmd.type = CMD_SET_POS;
		cmd.data.transform.obj_type = TYPE_LIGHT;
		cmd.data.transform.index = gui->selection.index;
		cmd.data.transform.pos = gui->transform.pos;
		cmd_enqueue(gui, cmd);
	}
}

static t_transform	*get_sel_transform(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE)
		return (&sc->spheres[gui->selection.index].transform);
	if (gui->selection.type == TYPE_PLANE)
		return (&sc->planes[gui->selection.index].transform);
	if (gui->selection.type == TYPE_CYLINDER)
		return (&sc->cylinders[gui->selection.index].transform);
	if (gui->selection.type == TYPE_MESH)
		return (&sc->groups[gui->selection.index].transform);
	if (gui->selection.type == TYPE_LIGHT)
		return (&sc->lights[gui->selection.index].transform);
	return (NULL);
}

void	transform_panel_sync(t_gui *gui)
{
	t_transform	*src;
	double		r;

	src = get_sel_transform(gui);
	if (!src)
		return ;
	gui->transform.pos = src->pos;
	gui->transform.rotation = src->rotation;
	gui->transform.scale = src->scale;
	if (gui->selection.type == TYPE_SPHERE
		&& gui->selection.index < gui->scene->sphere_count)
	{
		r = sqrt(gui->scene->spheres[gui->selection.index].radius_sq);
		gui->transform.scale = vec3(r, r, r);
	}
	else if (gui->selection.type == TYPE_CYLINDER
		&& gui->selection.index < gui->scene->cylinder_count)
	{
		r = sqrt(gui->scene->cylinders[gui->selection.index].radius_sq);
		gui->transform.scale = vec3(r, r, gui->transform.scale.z);
	}
}

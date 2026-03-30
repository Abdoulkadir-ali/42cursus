/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"
#include <math.h>

void	reset_camera_view(t_gui *gui)
{
	t_vec3	f;

	if (!gui->cam_ctrl.camera)
		return ;
	f = gui->cam_ctrl.camera->transform.forward;
	gui->cam_ctrl.transform = gui->cam_ctrl.camera->transform;
	gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
	gui->cam_ctrl.target_rot.pitch = asin(f.y);
	gui->cam_ctrl.target_pos = gui->cam_ctrl.camera->transform.pos;
	gui->cam_ctrl.target_fov = gui->cam_ctrl.camera->fov;
}

void	gui_next_map(t_gui *gui)
{
	t_map_entry	*next;

	if (!gui->map_info.head || !gui->map_info.current)
		return ;
	if (gui->map_job.active)
		return ;
	if (gui->map_info.current->next)
		next = gui->map_info.current->next;
	else
		next = gui->map_info.head;
	if (next == gui->map_info.current)
		return ;
	map_load_async(gui, next);
}

void	gui_prev_map(t_gui *gui)
{
	t_map_entry	*entry;
	t_map_entry	*prev;

	if (!gui->map_info.head || !gui->map_info.current)
		return ;
	if (gui->map_job.active)
		return ;
	entry = gui->map_info.head;
	prev = NULL;
	while (entry && entry != gui->map_info.current)
	{
		prev = entry;
		entry = entry->next;
	}
	if (!prev)
	{
		prev = gui->map_info.head;
		while (prev->next)
			prev = prev->next;
	}
	if (prev == gui->map_info.current)
		return ;
	map_load_async(gui, prev);
}

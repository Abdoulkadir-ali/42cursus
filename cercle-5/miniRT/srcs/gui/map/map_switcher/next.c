/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

bool	load_scene_and_bvh(t_gui *gui, const char *path);

static void	reset_camera_view(t_gui *gui)
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
	char	*path;

	if (gui->map_info.count == 0)
		return ;
	gui->map_info.current_idx = (gui->map_info.current_idx + 1)
		% gui->map_info.count;
	path = gui->map_info.files[gui->map_info.current_idx];
	if (load_scene_and_bvh(gui, path))
	{
		gui->cam_ctrl.camera = &gui->scene->camera;
		reset_camera_view(gui);
		gui->render.dirty = true;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:01:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	reset_cam_ctrl(t_gui *gui)
{
	t_vec3	f;

	gui->cam_ctrl.camera = &gui->scene->camera;
	gui->cam_ctrl.transform = gui->scene->camera.transform;
	f = gui->scene->camera.transform.forward;
	gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
	gui->cam_ctrl.target_rot.pitch = asin(f.y);
	gui->cam_ctrl.target_pos = gui->scene->camera.transform.pos;
	gui->cam_ctrl.target_fov = gui->scene->camera.fov;
}

void	scene_reset(t_gui *gui)
{
	t_scene_snap	*snap;
	t_scene			*sc;

	if (!gui->map_info.current)
		return ;
	snap = &gui->map_info.current->snap;
	sc = gui->scene;
	reset_primitives(sc, snap);
	reset_meshes(sc, snap);
	reset_groups(sc, snap);
	reset_extra(sc, snap);
	sc->ambient = snap->ambient;
	sc->camera = snap->camera;
	gui->ambient_color = snap->ambient_color;
	gui->ambient_intensity = snap->ambient_intensity;
	reset_cam_ctrl(gui);
	clear_selection(gui);
	{ t_cmd _c; ft_memset(&_c, 0, sizeof(_c)); _c.type = CMD_REBUILD_BVH; cmd_enqueue(gui, _c); }
}

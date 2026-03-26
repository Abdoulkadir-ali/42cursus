/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

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

/**
 * @brief Restores the scene to its initial post-parsing state from snapshot.
 * @param gui Pointer to the GUI context.
 */
void	scene_reset(t_gui *gui)
{
	t_scene_snap	*s;
	t_scene			*sc;

	if (!gui->map_info.current)
		return ;
	s = &gui->map_info.current->snap;
	sc = gui->scene;
	reset_sphere(sc, s);
	reset_plane(sc, s);
	reset_cylinder(sc, s);
	reset_cone(sc, s);
	reset_light(sc, s);
	reset_box(sc, s);
	reset_capsule(sc, s);
	reset_rect(sc, s);
	reset_pyramid(sc, s);
	reset_tri(sc, s);
	reset_mesh(sc, s);
	reset_material(sc, s);
	sc->ambient = s->ambient;
	sc->camera = s->camera;
	gui->ambient_color = s->ambient_color;
	gui->ambient_intensity = s->ambient_intensity;
	reset_cam_ctrl(gui);
	clear_selection(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}

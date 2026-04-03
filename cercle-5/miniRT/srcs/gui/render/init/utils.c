/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:48:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:52:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	init_window(t_gui *gui)
{
	if (!gui->win.mlx)
		return (false);
	gui->win.win = mlx_new_window(gui->win.mlx, gui->win.size.x,
			gui->win.size.y, "miniRT");
	if (!gui->win.win)
		return (false);
	gui->win.img = mlx_new_image(gui->win.mlx, gui->win.size.x,
			gui->win.size.y);
	gui->win.addr = mlx_get_data_addr(gui->win.img, &gui->win.bpp,
			&gui->win.line_len, &gui->win.endian);
	gui->win.disp_size = gui->win.size;
	gui->win.disp_img = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.disp_addr = mlx_get_data_addr(gui->win.disp_img,
			&gui->win.disp_bpp, &gui->win.disp_line_len, &gui->win.disp_endian);
	gui->win.gui_bg_img = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.gui_bg_addr = mlx_get_data_addr(gui->win.gui_bg_img,
			&gui->win.gui_bg_bpp, &gui->win.gui_bg_line_len,
			&gui->win.gui_bg_endian);
	return (true);
}

void	init_camera(t_gui *gui)
{
	t_vec3	f;

	gui->cam_ctrl.camera = &gui->scene->camera;
	gui->cam_ctrl.transform = gui->scene->camera.transform;
	f = gui->cam_ctrl.camera->transform.forward;
	gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
	gui->cam_ctrl.target_rot.pitch = asin(f.y);
	gui->cam_ctrl.target_pos = gui->cam_ctrl.camera->transform.pos;
	gui->cam_ctrl.target_fov = gui->cam_ctrl.camera->fov;
	gui->cam_ctrl.move_speed = 0.5;
	gui->cam_ctrl.lerp_factor = 0.1;
	gui->render.scale = 1;
	gui->render.dirty = true;
	gui->widgets = NULL;
}

void	gui_init_physics(t_gui *gui)
{
	gui->physics_enabled = true;
	gui->phys_accumulator = 0.0;
	gui->phys_fixed_dt = 1.0 / 60.0;
	gui->phys_max_steps = 5;
	gui->ambient_color = 0xFFFFFF;
	gui->ambient_intensity = 1.0;
	gui->phys_engine.scene = gui->scene;
	gui->phys_engine.settings.slop = 0.005;
	gui->phys_engine.settings.baumgarte = 0.2;
	gui->phys_engine.settings.solver_iterations = 10;
	gui->phys_engine.settings.restitution_slop = 0.5;
	gui->phys_engine.settings.gravity = vec3(0, -9.81, 0);
	gui->phys_engine.settings.global_damping = 0.999;
	gui->phys_engine.settings.time_scale = 1.0;
	gui->phys_engine.settings.mesh_simplify_collision = 0;
	gui->phys_engine.pool.initialized = 0;
}

void	gui_init_render(t_gui *gui)
{
	gui->render.num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (gui->render.num_cores < 1)
		gui->render.num_cores = 1;
	if (gui->render.num_cores > 128)
		gui->render.num_cores = 128;
	gui->render.pool.ready = false;
}


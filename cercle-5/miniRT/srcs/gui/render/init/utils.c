/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:48:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:15:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_display_buffers(t_gui *gui)
{
	gui->win.disp_imgs[0] = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.disp_addrs[0] = mlx_get_data_addr(gui->win.disp_imgs[0],
			&gui->win.disp_bpp, &gui->win.disp_line_len, &gui->win.disp_endian);
	gui->win.disp_imgs[1] = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.disp_addrs[1] = mlx_get_data_addr(gui->win.disp_imgs[1],
			&gui->win.disp_bpp, &gui->win.disp_line_len, &gui->win.disp_endian);
	gui->win.disp_imgs[2] = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.disp_addrs[2] = mlx_get_data_addr(gui->win.disp_imgs[2],
			&gui->win.disp_bpp, &gui->win.disp_line_len, &gui->win.disp_endian);
	gui->win.gui_bg_img = mlx_new_image(gui->win.mlx, gui->win.disp_size.x,
			gui->win.disp_size.y);
	gui->win.gui_bg_addr = mlx_get_data_addr(gui->win.gui_bg_img,
			&gui->win.gui_bg_bpp, &gui->win.gui_bg_line_len,
			&gui->win.gui_bg_endian);
}

static void	init_camera_state(t_gui *gui)
{
	gui->cam_ctrl.move_speed = 0.5;
	gui->cam_ctrl.lerp_factor = 0.1;
	gui->cam_ctrl.moving_forward = false;
	gui->cam_ctrl.moving_backward = false;
	gui->cam_ctrl.moving_left = false;
	gui->cam_ctrl.moving_right = false;
	gui->cam_ctrl.moving_up = false;
	gui->cam_ctrl.moving_down = false;
	gui->cam_ctrl.zooming_in = false;
	gui->cam_ctrl.zooming_out = false;
	gui->cam_ctrl.mouse_left_pressed = false;
	gui->cam_ctrl.mouse_middle_pressed = false;
	gui->cam_ctrl.last_mouse = vec2i(0, 0);
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
	gui->cam_ctrl.transform.rotation.yaw = gui->cam_ctrl.target_rot.yaw;
	gui->cam_ctrl.transform.rotation.pitch = gui->cam_ctrl.target_rot.pitch;
	init_camera_state(gui);
	gui->render.scale = 4;
	gui->win.size.x = gui->win.disp_size.x / gui->render.scale;
	gui->win.size.y = gui->win.disp_size.y / gui->render.scale;
	gui->win.line_len = gui->win.size.x * 4;
	gui->render.dirty = true;
	gui->widgets = NULL;
}

bool	init_window(t_gui *gui)
{
	size_t	max_n;

	if (!gui->win.mlx)
		return (false);
	gui->win.win = mlx_new_window(gui->win.mlx, gui->win.size.x,
			gui->win.size.y, "miniRT");
	if (!gui->win.win)
		return (false);
	max_n = gui->win.size.x * gui->win.size.y;
	gui->win.render_pixels = ft_calloc(max_n, sizeof(uint32_t));
	if (!gui->win.render_pixels)
		return (false);
	gui->win.img = NULL;
	gui->win.addr = (char *)gui->win.render_pixels;
	gui->win.bpp = 32;
	gui->win.line_len = gui->win.size.x * 4;
	gui->win.endian = 0;
	gui->win.disp_size = gui->win.size;
	init_display_buffers(gui);
	return (true);
}
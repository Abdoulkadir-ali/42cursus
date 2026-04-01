/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Initializes MLX window and image.
** Creates both the render image (fixed resolution) and display image.
** Returns false on failure.
*/
static bool	init_window(t_gui *gui)
{
	if (!gui->win.mlx)
		return (false);
	gui->win.win = mlx_new_window(gui->win.mlx, gui->win.width, gui->win.height,
			"miniRT");
	if (!gui->win.win)
		return (false);
	gui->win.img = mlx_new_image(gui->win.mlx, gui->win.width, gui->win.height);
	gui->win.addr = mlx_get_data_addr(gui->win.img, &gui->win.bpp,
			&gui->win.line_len, &gui->win.endian);
	gui->win.disp_w = gui->win.width;
	gui->win.disp_h = gui->win.height;
	gui->win.disp_img = mlx_new_image(gui->win.mlx, gui->win.disp_w,
			gui->win.disp_h);
	gui->win.disp_addr = mlx_get_data_addr(gui->win.disp_img,
			&gui->win.disp_bpp, &gui->win.disp_line_len, &gui->win.disp_endian);
	gui->win.gui_bg_img = mlx_new_image(gui->win.mlx, gui->win.disp_w,
			gui->win.disp_h);
	gui->win.gui_bg_addr = mlx_get_data_addr(gui->win.gui_bg_img,
			&gui->win.gui_bg_bpp, &gui->win.gui_bg_line_len,
			&gui->win.gui_bg_endian);
	return (true);
}

/*
** Sets up camera controller default values.
*/
static void	init_camera(t_gui *gui)
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

/*
** Main initialization function for the GUI subsystem.
** Allocates memory and initializes MLX, window, camera, and map switcher.
*/
static void	gui_init_physics(t_gui *gui)
{
	gui->physics_enabled = true;
	gui->phys_accumulator = 0.0;
	gui->phys_fixed_dt = 1.0 / 60.0;
	gui->phys_max_steps = 5;
	gui->ambient_color = 0xFFFFFF;
	gui->ambient_intensity = 1.0;
}

static void	gui_init_render(t_gui *gui)
{
	gui->render.num_cores = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (gui->render.num_cores < 1)
		gui->render.num_cores = 1;
	if (gui->render.num_cores > 128)
		gui->render.num_cores = 128;
	gui->render.pool.ready = false;
}

t_gui	*gui_init(t_scene *scene, void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	ft_memset(gui, 0, sizeof(t_gui));
	gui->win.width = RENDER_W;
	gui->win.height = RENDER_H;
	gui->win.mlx = mlx;
	gui->scene = scene;
	gui_init_physics(gui);
	gui_init_render(gui);
	if (!init_window(gui))
	{
		free(gui);
		return (NULL);
	}
	init_camera(gui);
	gui_map_switcher_init(gui);
	widget_init_default(gui);
	editor_init(gui);
	mlx_hook(gui->win.win, 22, 1L << 17, gui_window_resize, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	return (gui);
}

/*
** Cleans up GUI resources including MLX window, image, and map data.
*/
void	gui_destroy(t_gui *gui)
{
	if (!gui)
		return ;
	map_manager_destroy(gui);
	if (gui->win.gui_bg_img)
		mlx_destroy_image(gui->win.mlx, gui->win.gui_bg_img);
	if (gui->win.disp_img)
		mlx_destroy_image(gui->win.mlx, gui->win.disp_img);
	if (gui->win.img)
		mlx_destroy_image(gui->win.mlx, gui->win.img);
	if (gui->win.win)
		mlx_destroy_window(gui->win.mlx, gui->win.win);
	if (gui->win.mlx)
		free(gui->win.mlx);
	free(gui);
}

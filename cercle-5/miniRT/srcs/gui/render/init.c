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

#include "editor.h"

/*
** Main initialization function for the GUI subsystem.
** Allocates memory and initializes MLX, window, camera, and map switcher.
*/
extern void	*render_tile_worker(void *arg);


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

bool	gui_init(t_gui *gui, t_scene *scene, void *mlx)
{
	int		i;

	if (!gui)
		return (false);
	ft_memset(gui, 0, sizeof(t_gui));
	gui->scene = scene;
	gui->win.width = RENDER_W;
	gui->win.height = RENDER_H;
	gui->win.mlx = mlx;
	/* Initialize new GUI state */
	gui->physics_enabled = true;
	gui->phys_accumulator = 0.0;
	gui->phys_fixed_dt = 1.0 / 60.0;
	gui->phys_max_steps = 5;
	gui->ambient_color = 0xFFFFFF;
	gui->ambient_intensity = 1.0;
	gui->render.num_cores = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (gui->render.num_cores < 1)
		gui->render.num_cores = 1;
	if (gui->render.num_cores > 128)
		gui->render.num_cores = 128;
	gui->render.threads = malloc(sizeof(pthread_t)
			* (size_t)gui->render.num_cores);
	if (!gui->render.threads)
		return (false);
	if (!init_window(gui))
	{
		free(gui->render.threads);
		return (false);
	}
	gui->selection = malloc(sizeof(t_selection));
	gui->inspector = malloc(sizeof(t_inspector));
	gui->scene_panel = malloc(sizeof(t_scene_panel));
	gui->slider_state = malloc(sizeof(t_slider_state));
	gui->crud = malloc(sizeof(t_crud_ui));
	gui->hover = malloc(sizeof(t_hover_cache));
	if (!gui->selection || !gui->inspector || !gui->scene_panel
		|| !gui->slider_state || !gui->crud || !gui->hover)
		return (false);
	ft_memset(gui->selection, 0, sizeof(t_selection));
	ft_memset(gui->inspector, 0, sizeof(t_inspector));
	ft_memset(gui->scene_panel, 0, sizeof(t_scene_panel));
	ft_memset(gui->slider_state, 0, sizeof(t_slider_state));
	ft_memset(gui->crud, 0, sizeof(t_crud_ui));
	ft_memset(gui->hover, 0, sizeof(t_hover_cache));
	init_camera(gui);
	gui_map_switcher_init(gui);
	widget_init_default(gui);
	editor_init(gui);
	i = 0;
	while (i < gui->render.num_cores)
	{
		gui->pool.args[i].idx = i;
		gui->pool.args[i].gui = gui;
		sem_init(&gui->pool.start[i], 0, 0);
		sem_init(&gui->pool.done[i], 0, 0);
		pthread_create(&gui->pool.threads[i], NULL, render_tile_worker,
			&gui->pool.args[i]);
		i++;
	}
	gui->pool.n = gui->render.num_cores;
	gui->pool.ready = true;
	ft_memset(&gui->rt, 0, sizeof(t_rt_engine));
	raytrace_engine_sync(&gui->rt, scene, gui->win.width, gui->win.height);
	mlx_hook(gui->win.win, 22, 1L << 17, gui_window_resize, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	return (true);
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
	if (gui->render.threads)
		free(gui->render.threads);
	int j = 0;
	gui->pool.shutdown = true;
	while (j < gui->pool.n)
	{
		sem_post(&gui->pool.start[j]);
		pthread_join(gui->pool.threads[j], NULL);
		sem_destroy(&gui->pool.start[j]);
		sem_destroy(&gui->pool.done[j]);
		j++;
	}
	free(gui->selection);
	free(gui->inspector);
	free(gui->scene_panel);
	free(gui->slider_state);
	free(gui->crud);
	free(gui->hover);
	rt_engine_cleanup(&gui->rt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:37:57 by abdoali          ###   ########.fr       */
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
	gui->win.win = mlx_new_window(gui->win.mlx, gui->win.size.x, gui->win.size.y,
			"miniRT");
	if (!gui->win.win)
		return (false);
	gui->win.img = mlx_new_image(gui->win.mlx, gui->win.size.x, gui->win.size.y);
	gui->win.addr = mlx_get_data_addr(gui->win.img, &gui->win.bpp,
			&gui->win.line_len, &gui->win.endian);
	gui->win.disp_size.x = gui->win.size.x;
	gui->win.disp_size.y = gui->win.size.y;
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
	gui->cam_ctrl.basis_dirty = true;
	gui->render.scale = 1;
	gui->render.dirty = true;
	gui->render.proj_dirty = true;
	gui->widgets = NULL;
}

static bool	init_gui_managers(t_gui *gui)
{
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
	return (true);
}

static bool	init_render_pool(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < gui->render.num_cores)
	{
		gui->pool.args[i].idx = i;
		gui->pool.args[i].gui = gui;
		if (sem_init(&gui->pool.start[i], 0, 0) != 0
			|| sem_init(&gui->pool.done[i], 0, 0) != 0)
			return (gui->pool.n = i, false);
		if (pthread_create(&gui->pool.threads[i], NULL, render_tile_worker,
				&gui->pool.args[i]) != 0)
			return (gui->pool.n = i, false);
		i++;
	}
	gui->pool.n = gui->render.num_cores;
	gui->pool.ready = true;
	return (true);
}

static void	init_gui_state(t_gui *gui, void *mlx)
{
	gui->win.size.x = RENDER_W;
	gui->win.size.y = RENDER_H;
	gui->win.mlx = mlx;
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
}

bool	gui_init(t_gui *gui, t_scene *scene, void *mlx)
{
	if (!gui || (ft_memset(gui, 0, sizeof(t_gui)), 0))
		return (false);
	gui->scene = scene;
	init_gui_state(gui, mlx);
	gui->render.threads = malloc(sizeof(pthread_t) * gui->render.num_cores);
	if (!gui->render.threads || !init_window(gui))
		return (free(gui->render.threads), false);
	if (!init_gui_managers(gui))
		return (gui_destroy(gui), false);
	init_camera(gui);
	gui_map_switcher_init(gui);
	widget_init_default(gui);
	editor_init(gui);
	if (!init_render_pool(gui))
		return (gui_destroy(gui), false);
	pthread_rwlock_init(&gui->scene_lock, NULL);
	gui->render.proj_dirty = true;
	raytrace_engine_sync(&gui->rt, scene, gui->win.size.x, gui->win.size.y);
	gui->phys = phys_create(scene);
	scene->phys = gui->phys;
	mlx_hook(gui->win.win, 22, 1L << 17, gui_window_resize, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	return (true);
}

static void	free_widgets(t_gui *gui)
{
	t_widget	*w;
	t_widget	*next;

	w = gui->widgets;
	while (w)
	{
		next = w->next;
		free(w->label);
		free(w);
		w = next;
	}
	gui->widgets = NULL;
}

/*
** Cleans up GUI resources including MLX window, image, and map data.
*/
void	gui_destroy(t_gui *gui)
{
	if (!gui)
		return ;
	mlx_loop_end(gui->win.mlx);
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
	free_widgets(gui);
	pthread_rwlock_destroy(&gui->scene_lock);
	phys_destroy(gui->phys);
	rt_engine_cleanup(&gui->rt);
}

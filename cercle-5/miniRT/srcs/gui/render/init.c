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

#include "gui.h"

/*
** Initializes MLX window and image.
** Returns false on failure.
*/
static bool	init_window(t_gui *gui)
{
	if (!gui->win.mlx)
		return (false);
	gui->win.win = mlx_new_window(gui->win.mlx, gui->win.width,
			gui->win.height, "miniRT");
	if (!gui->win.win)
	{
		free(gui->win.mlx);
		return (false);
	}
	gui->win.img = mlx_new_image(gui->win.mlx, gui->win.width, gui->win.height);
	gui->win.addr = mlx_get_data_addr(gui->win.img, &gui->win.bpp,
			&gui->win.line_len, &gui->win.endian);
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
t_gui	*gui_init(t_scene *scene, t_bvh *bvh, void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	ft_memset(gui, 0, sizeof(t_gui));
	gui->scene = scene;
	gui->bvh = bvh;
	gui->win.width = 1280;
	gui->win.height = 720;
	gui->win.mlx = mlx;
	if (!init_window(gui))
	{
		free(gui);
		return (NULL);
	}
	init_camera(gui);
	gui_map_switcher_init(gui);
	return (gui);
}

/*
** Cleans up GUI resources including MLX window, image, and map data.
*/
void	gui_destroy(t_gui *gui)
{
	int	i;

	if (!gui)
		return ;
	if (gui->win.img)
		mlx_destroy_image(gui->win.mlx, gui->win.img);
	if (gui->win.win)
		mlx_destroy_window(gui->win.mlx, gui->win.win);
	if (gui->win.mlx)
		free(gui->win.mlx);
	if (gui->map_info.files)
	{
		i = 0;
		while (i < gui->map_info.count)
		{
			free(gui->map_info.files[i]);
			i++;
		}
		free(gui->map_info.files);
	}
	free(gui);
}


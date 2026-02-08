/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_gui	*gui_init(t_scene *scene, t_bvh *bvh)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	ft_memset(gui, 0, sizeof(t_gui)); // Safer initialization
	
	gui->scene = scene;
	gui->bvh = bvh;
	gui->width = 1280;
	gui->height = 720;
	
	gui->mlx = mlx_init();
	if (!gui->mlx)
	{
		free(gui);
		return (NULL);
	}
	gui->win = mlx_new_window(gui->mlx, gui->width, gui->height, "miniRT");
	gui->img = mlx_new_image(gui->mlx, gui->width, gui->height);
	gui->addr = mlx_get_data_addr(gui->img, &gui->bits_per_pixel,
			&gui->line_length, &gui->endian);
	
	// Camera setup: use direct reference from scene
	gui->camera = &scene->camera;
	
	// Set initial view parameters based on camera
	t_vec3 f = gui->camera->transform.forward;
	gui->rotation.yaw = atan2(f.x, f.z);
	gui->rotation.pitch = asin(f.y);
	
	gui->target_rotation = gui->rotation;
	gui->target_position = gui->camera->transform.pos;
	gui->target_fov = gui->camera->fov;
	
	gui->move_speed = 0.5;
	gui->lerp_factor = 0.1;
	gui->render_scale = 1;
	gui->dirty = true;
	gui->widgets = NULL;

	gui_map_switcher_init(gui);
	return (gui);
}

void	gui_destroy(t_gui *gui)
{
	int	i;

	if (!gui)
		return ;
	if (gui->img)
		mlx_destroy_image(gui->mlx, gui->img);
	if (gui->win)
		mlx_destroy_window(gui->mlx, gui->win);
	if (gui->mlx)
	{
		// Note: Some MLX versions need cleanup, some don't.
		// Standard minilibx-linux doesn't have a destroy_display usually,
		// but let's stick to basics.
		free(gui->mlx);
	}
	if (gui->maps)
	{
		for (i = 0; i < gui->map_count; i++)
			free(gui->maps[i]);
		free(gui->maps);
	}
	free(gui);
}


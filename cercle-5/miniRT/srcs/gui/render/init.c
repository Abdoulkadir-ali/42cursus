/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:01:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 20:01:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Initializes MLX window and image.
** Creates both the render image (fixed resolution) and display image.
** Returns false on failure.
*/
t_gui	*gui_init(t_scene *scene, void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	ft_memset(gui, 0, sizeof(t_gui));
	gui->win.size.x = RENDER_W;
	gui->win.size.y = RENDER_H;
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
	mlx_hook(gui->win.win, 22, 1L << 17, (void *)gui_window_resize, gui);
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

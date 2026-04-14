/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:12:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:13:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "optimizations.h"

t_gui	*gui_init(t_scene *scene, void *mlx)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	ft_memset(gui, 0, sizeof(t_gui));
	gui->scene = scene;
	gui->win.mlx = mlx;
	gui->win.size = (t_vec2s){RENDER_W, RENDER_H};
	if (!init_window(gui))
	{
		free(gui);
		return (NULL);
	}
	init_camera(gui);
	gui_init_physics(gui);
	gui_init_anim(gui);
	gui_init_render(gui);
	gui_map_switcher_init(gui);
	editor_init(gui);
	settings_init(gui);
	return (gui);
}

void	gui_destroy(t_gui *gui)
{
	if (!gui)
		return ;
	destroy_phys_pool(&gui->phys_engine);
	map_manager_destroy(gui);
	if (gui->win.render_pixels)
		free(gui->win.render_pixels);
	if (gui->win.win)
		mlx_destroy_window(gui->win.mlx, gui->win.win);
	if (gui->win.img)
		mlx_destroy_image(gui->win.mlx, gui->win.img);
	if (gui->win.disp_imgs[0])
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[0]);
	if (gui->win.disp_imgs[1])
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[1]);
	if (gui->win.disp_imgs[2])
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[2]);
	if (gui->win.gui_bg_img)
		mlx_destroy_image(gui->win.mlx, gui->win.gui_bg_img);
	opts_free(gui);
	free(gui);
}

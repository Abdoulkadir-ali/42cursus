/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:40:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 20:57:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_gui	init_gui(t_window *window, t_camera *camera, t_map_manager *map_manager, t_render_config *render_config, t_map *map)
{
	t_gui	gui;

	gui.window = window;
	gui.gui_style = camera->gui_style;
	gui.map_manager = map_manager;
	gui.render_config = render_config;
	gui.camera = camera;
	gui.map = map;
	return (gui);
}

int	init_gui_images(t_gui *gui)
{
	gui->window->gui_img.img = mlx_new_image(gui->window->mlx_ptr, GUI_PANEL_WIDTH,
			gui->window->height);
	if (!gui->window->gui_img.img)
		return (0);
	gui->window->gui_img.img_addr = mlx_get_data_addr(gui->window->gui_img.img, &gui->window->gui_img.img_bpp,
			&gui->window->gui_img.img_line_len, &gui->window->gui_img.img_endian);
	if (!gui->window->gui_img.img_addr)
		return (0);
	return (1);
}
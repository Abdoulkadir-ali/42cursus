/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:40:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:21:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_gui	*init_gui(t_gui_args args)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->window = args.window;
	gui->gui_style = args.camera->gui_style;
	gui->maps = args.maps;
	gui->render_config = args.render_config;
	gui->camera = args.camera;
	gui->map = args.map;
	if (!init_gui_images(gui))
	{
		free(gui);
		return (NULL);
	}
	return (gui);
}

int	init_gui_images(t_gui *gui)
{
	int	bpp;
	int	line_len;

	gui->window->gui_img.img = mlx_new_image(gui->window->mlx_ptr,
			GUI_PANEL_WIDTH, gui->window->height);
	if (!gui->window->gui_img.img)
		return (0);
	gui->window->gui_img.img_addr = mlx_get_data_addr(gui->window->gui_img.img,
			&bpp, &line_len, &gui->window->gui_img.img_endian);
	gui->window->gui_img.img_bpp = (size_t)bpp;
	gui->window->gui_img.img_line_len = (size_t)line_len;
	if (!gui->window->gui_img.img_addr)
		return (0);
	return (1);
}

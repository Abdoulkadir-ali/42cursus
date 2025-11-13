/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:24:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:43:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	render_scene(t_data *data)
{
	draw_grid(data->graphics);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->window->main_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->window->gui_img.img, 0, 0);
	render_gui(data->gui);
	return (1);
}

int	init_and_render(t_data *data)
{
	t_graphics			*g;

	data->gui = init_gui((t_gui_args){data->window, data->camera, &data->maps, &data->graphics->render_config, data->maps.current_map});
	if (!init_gui_images(data->gui))
		return (0);
	g = data->graphics;
	g->map = data->maps.current_map;
	g->camera = data->camera;
	data->camera_ctx->map = data->maps.current_map;
	adjust_camera_to_map(data->camera_ctx);
	render_scene(data);
	return (1);
}
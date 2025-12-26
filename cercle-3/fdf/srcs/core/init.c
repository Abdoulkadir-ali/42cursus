/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:52:25 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:29:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_defaults(t_data *data)
{
	data->graphics->render_config.render_mode = RENDER_LINES;
	data->graphics->render_config.lod_value = DEFAULT_LOD_LEVEL;
	data->graphics->render_config.use_depth_culling = 1;
}

int	init_window_main_image(t_window *win, void *mlx)
{
	t_image	*main_img;
	int		bpp;
	int		line_len;
	int		endian;

	main_img = &win->main_img;
	main_img->img = mlx_new_image(mlx, win->width, win->height);
	if (!main_img->img)
		return (0);
	main_img->img_addr = mlx_get_data_addr(main_img->img, &bpp, &line_len,
			&endian);
	main_img->img_bpp = (size_t)bpp;
	main_img->img_line_len = (size_t)line_len;
	main_img->img_endian = endian;
	if (!main_img->img_addr)
		return (0);
	win->z_buffer = malloc(sizeof(float) * win->width * win->height);
	if (!win->z_buffer)
		return (0);
	return (1);
}

int	init_window_system(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->window = init_window(data->mlx_ptr);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window->width,
			data->window->height, "FDF - Advanced Controls");
	if (!data->win_ptr)
		return (0);
	data->window->ptr = data->win_ptr;
	return (1);
}

int	init_and_render(t_data *data)
{
	t_graphics	*g;

	data->gui = init_gui((t_gui_args){data->window,
			data->camera_manager->camera, &data->map_manager,
			&data->graphics->render_config, data->map_manager.current_map});
	if (!data->gui)
		return (0);
	g = data->graphics;
	g->map = data->map_manager.current_map;
	g->camera = data->camera_manager->camera;
	data->camera_manager->map = data->map_manager.current_map;
	adjust_camera_to_map(data->camera_manager);
	return (1);
}

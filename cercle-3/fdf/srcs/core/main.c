/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:13:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	init_mlx_and_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->window = init_window(data->mlx_ptr);
	init_window_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.width,
			data->window.height, "FDF - Advanced Controls");
	if (!data->win_ptr)
		return (0);
	data->window.ptr = data->win_ptr;
	data->camera = init_camera();
	data->graphics = init_graphics(&data->window, &data->camera);
	return (1);
}

static int	init_map_and_image(t_data *data)
{
	init_map_list(&data->graphics.map_manager);
	if (data->graphics.map_manager.count > 0)
		data->map = data->graphics.map_manager.maps[0];
	else
		data->map = create_test_grid();
	if (!data->map)
		return (0);
	data->window.main_img.img = mlx_new_image(data->mlx_ptr, data->window.width, data->window.height);
	if (!data->window.main_img.img)
		return (0);
	data->window.main_img.img_addr = mlx_get_data_addr(data->window.main_img.img, &data->window.main_img.img_bpp,
			&data->window.main_img.img_line_len, &data->window.main_img.img_endian);
	if (!data->window.main_img.img_addr)
		return (0);
	data->window.z_buffer = malloc(sizeof(float) * data->window.width * data->window.height);
	if (!data->window.z_buffer)
		return (0);
	data->graphics.map = data->map;
	return (1);
}

static int	init_and_render(t_data *data)
{
	apply_map_style(data->map);
	data->gui = init_gui(&data->window, &data->camera, &data->graphics.map_manager, &data->graphics.render_config, data->map);
	if (!init_gui_images(&data->gui))
		return (0);
	data->graphics.map = data->map;
	data->graphics.camera = &data->camera;
	data->graphics.render_config.render_mode = data->render_mode;
	data->graphics.render_config.lod_level = data->lod_level;
	data->graphics.render_config.use_depth_culling = data->use_depth_culling;
	data->graphics.render_config.fill_triangles = data->fill_triangles;
	draw_panel_background(&data->gui);
	draw_grid(&data->graphics);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window.main_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->window.gui_img.img, 0, 0);
	render_gui(&data->gui);
	return (1);
}

int	main(void)
{
	t_data			data;
	struct timeval	tv;

	if (!init_mlx_and_window(&data))
		return (1);
	init_mouse(&data.graphics.mouse);
	init_keys(&data.graphics.keys);
	init_map_config(&data);
	gettimeofday(&tv, NULL);
	data.last_frame_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data.frame_in_progress = 0;
	data.graphics.render_config.lod_level = 2;
	data.graphics.render_config.render_mode = RENDER_LINES;
	data.graphics.map_config.line_thickness = 1;
	data.graphics.map_config.point_thickness = 0;
	data.graphics.map_config.line_color = 0xFFFFFF;
	data.graphics.map_config.point_color = 0xFFFFFF;
	data.graphics.map_config.style = 0;
	data.camera.use_z_divisor = 1;
	data.use_depth_culling = 0;
	data.fill_triangles = 0;
	data.lod_level = 2;
	data.render_mode = RENDER_LINES;
	if (!init_map_and_image(&data))
		return (1);
	data.map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(data.map);
	if (!init_and_render(&data))
		return (1);
	t_events events = {
		&data.camera,
		&data.window,
		data.map,
		&data.graphics,
		&data.gui,
		data.render_mode,
		data.lod_level,
		data.use_depth_culling,
		data.fill_triangles
	};
	setup_hooks(&events);
	mlx_loop(data.mlx_ptr);
	return (0);
}

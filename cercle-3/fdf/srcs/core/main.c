/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/14 18:27:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_defaults(t_data *data);

int	main(int argc, char **argv)
{
	t_data		data = {0};
	t_events	*events;

	if (argc > 2)
	{
		printf("Usage: ./fdf [map.fdf]\n");
		return (1);
	}

	printf("[dbg] main: argc=%d argv1=%s\n", argc, (argc>1?argv[1]:"(none)"));
	// Window initialization
	if (!init_window_system(&data))
		return (1);
	printf("[dbg] after init_window_system: mlx_ptr=%p window=%p\n", data.mlx_ptr, data.window);
	if (data.window)
		printf("[dbg] window size: %dx%d\n", data.window->width, data.window->height);
	if (!init_window_main_image(data.window, data.mlx_ptr))
		return (1);
	if (data.window)
		printf("[dbg] after init_window_main_image: main_img.img=%p img_addr=%p bpp=%d line_len=%d\n",
			data.window->main_img.img, data.window->main_img.img_addr,
			data.window->main_img.img_bpp, data.window->main_img.img_line_len);

	// Map initialization
	if (argc == 2)
	{
		data.map_manager.current_map = load_map(argv[1]);
		if (!data.map_manager.current_map)
		{
			return (1);
		}
		printf("[dbg] loaded map %s -> %p size=%dx%d\n", argv[1], data.map_manager.current_map,
			data.map_manager.current_map->width, data.map_manager.current_map->height);
		data.map_manager.map_files = (char **)&argv[1];
	}
	else
	{
		data.map_manager.current_map = create_test_grid();
		if (!data.map_manager.current_map)
		{
			return (1);
		}
		data.map_manager.map_files = NULL;
	}
	data.map_manager.maps = &data.map_manager.current_map;
	data.map_manager.count = 1;
	data.map_manager.current_index = 0;

	// Camera initialization
	data.camera_ctx = init_camera((t_camera_args){data.map_manager.current_map, data.window});
	if (!data.camera_ctx)
	{
		return (1);
	}
	data.camera = data.camera_ctx->camera;
	if (data.camera)
		printf("[dbg] camera initialized: scale=%f proj=%d offset=(%f,%f)\n",
			data.camera->scale, data.camera->projection,
			data.camera->offset.x, data.camera->offset.y);

	// Graphics initialization
	data.graphics = init_graphics((t_graphics_args){data.window, data.camera, data.map_manager.current_map});
	if (!data.graphics)
	{
		return (1);
	}
	printf("[dbg] graphics initialized: %p\n", data.graphics);

	// Defaults
	init_defaults(&data);

	// Render initialization and first render
	if (!init_and_render(&data))
		return (1);
	printf("[dbg] init_and_render returned\n");

	// Events initialization
	events = init_events(&data);
	if (!events)
	{
		return (1);
	}
	setup_hooks(events);
	(void)events;

	mlx_loop(data.mlx_ptr);
	return (0);
}
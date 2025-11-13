/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 19:26:53 by abdoali          ###   ########.fr       */
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
	// Window initialization
	if (!init_window_system(&data))
		return (1);
	if (!init_window_main_image(data.window, data.mlx_ptr))
		return (1);

	// Map initialization
	if (argc == 2)
	{
		data.map_manager.current_map = load_map(argv[1]);
		if (!data.map_manager.current_map)
		{
			return (1);
		}
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

	// Graphics initialization
	data.graphics = init_graphics((t_graphics_args){data.window, data.camera, data.map_manager.current_map});
	if (!data.graphics)
	{
		return (1);
	}

	// Defaults
	init_defaults(&data);

	// Render initialization and first render
	if (!init_and_render(&data))
		return (1);

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
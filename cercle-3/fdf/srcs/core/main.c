/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:50:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	init_data_and_window(t_data *data, int argc)
{
	ft_memset(data, 0, sizeof(t_data));
	if (!init_window_system(data))
		return (0);
	if (!init_window_main_image(data->window, data->mlx_ptr))
		return (0);
	if (argc == 1)
		init_map_list(&data->map_manager, MAPS_DIR);
	return (1);
}

static int	init_camera_and_graphics(t_data *data, int argc, char **argv)
{
	char				*map_file;
	t_camera_args		cam_args;
	t_graphics_args		gfx_args;

	if (argc == 2)
		map_file = argv[1];
	else
		map_file = NULL;
	cam_args.map = NULL;
	cam_args.window = data->window;
	cam_args.manager = &data->map_manager;
	cam_args.map_file = map_file;
	data->camera_manager = init_camera(cam_args);
	if (!data->camera_manager)
		return (0);
	gfx_args.window = data->window;
	gfx_args.camera = data->camera_manager->camera;
	gfx_args.map = data->map_manager.current_map;
	data->graphics = init_graphics(gfx_args);
	if (!data->graphics)
		return (0);
	return (1);
}

static int	init_defaults_and_render(t_data *data)
{
	init_defaults(data);
	if (!init_and_render(data))
		return (0);
	return (1);
}

static int	init_events_and_hooks(t_data *data, t_events **events)
{
	*events = init_events(&(t_events_args){data->window, data->graphics,
			data->gui, data->camera_manager, &data->map_manager,
			data->map_manager.current_map});
	if (!*events)
		return (0);
	setup_hooks(*events);
	redraw(*events);
	if (data->gui)
		free(data->gui);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_events	*events;

	XInitThreads();
	if (!init_data_and_window(&data, argc))
		return (1);
	if (!init_camera_and_graphics(&data, argc, argv))
		return (1);
	if (!init_defaults_and_render(&data))
		return (1);
	if (!init_events_and_hooks(&data, &events))
		return (1);
	mlx_loop(data.mlx_ptr);
	return (0);
}

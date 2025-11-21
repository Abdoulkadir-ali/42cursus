/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:13:54 by abdoali          ###   ########.fr       */
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
	if (!init_window_system(&data))
		return (1);
	if (!init_window_main_image(data.window, data.mlx_ptr))
		return (1);
	/* populate map manager from maps/test_maps when no filename is provided */
	if (argc == 1)
		init_map_list(&data.map_manager);

	data.camera_manager = init_camera((t_camera_args){.map = NULL, .window = data.window, .manager = &data.map_manager, .map_file = (argc == 2) ? argv[1] : NULL});
	if (!data.camera_manager)
		return (1);
	data.graphics = init_graphics((t_graphics_args){data.window, data.camera_manager->camera, data.map_manager.current_map});
	if (!data.graphics)
		return (1);
	init_defaults(&data);
	if (!init_and_render(&data))
		return (1);
	events = init_events(&data);
	if (!events)
		return (1);
	setup_hooks(events);
	/* draw first frame immediately to avoid opening a black window */
	redraw(events);
	(void)events;

	mlx_loop(data.mlx_ptr);
	return (0);
}
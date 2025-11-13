/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:43:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_defaults(t_data *data);

int	main(void)
{
	t_data		data;
	t_events	*events;

	// Window initialization
	if (!init_window_system(&data))
		return (1);
	if (!init_window_main_image(data.window, data.mlx_ptr))
		return (1);

		// Map initialization
	data.maps = init_maps();
	data.maps.current_map = select_initial_map(&data.maps);
	if (!data.maps.current_map)
		return (1);

	// Camera initialization
	data.camera_ctx = init_camera((t_camera_args){data.maps.current_map, data.window});
	data.camera = data.camera_ctx->camera;

	// Graphics initialization
	data.graphics = init_graphics((t_graphics_args){data.window, data.camera, data.maps.current_map});

	// Defaults
	init_defaults(&data);

	// Render initialization and first render
	if (!init_and_render(&data))
		return (1);

	// Events initialization
	events = init_events(&data);
	setup_hooks(events);
	(void)events;

	mlx_loop(data.mlx_ptr);
	return (0);
}

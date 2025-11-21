/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:24:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 20:00:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_and_render(t_data *data)
{
	t_graphics			*g;

	data->gui = init_gui((t_gui_args){data->window, data->camera_manager->camera, &data->map_manager, &data->graphics->render_config, data->map_manager.current_map});
	if (!init_gui_images(data->gui))
		return (0);
	g = data->graphics;
	g->map = data->map_manager.current_map;
	g->camera = data->camera_manager->camera;
	data->camera_manager->map = data->map_manager.current_map;
	adjust_camera_to_map(data->camera_manager);
	return (1);
}
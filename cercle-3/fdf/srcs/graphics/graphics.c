/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 20:40:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"

void	redraw(t_events *events)
{
	t_graphics *g = events->graphics;
	/* --- Sync map and camera state from events --- */
	if (events->maps && events->maps->current_map)
		g->map = events->maps->current_map;

	if (events->camera_manager)
		update_zoom(events->camera_manager);

	g->camera = events->camera;

	g->render_config.render_mode = events->render_mode;
	g->render_config.lod_level = events->lod_level;
	g->render_config.use_depth_culling = events->use_depth_culling;
	g->render_config.fill_triangles = events->fill_triangles;
	/* debug sampling removed */

	clear_image(g);
	// clear_z_buffer(g);
	draw_grid(g);

	/* debug sampling removed */
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->main_img.img, 0, 0);
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->gui_img.img, 0, 0);
	render_gui(events->gui);
}
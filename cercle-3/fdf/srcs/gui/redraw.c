/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:29:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:13:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "graphics.h"
#include "gui.h"

void	redraw_panel(t_events *events);

void	redraw(t_events *events)
{
	t_graphics	*g;

	g = events->graphics;
	if (events->maps && events->maps->current_map)
		g->map = events->maps->current_map;
	if (events->camera_manager)
		update_zoom(events->camera_manager);
	cache_projections(g);
	g->camera = events->camera;
	g->render_config.render_mode = events->render_mode;
	g->render_config.lod_level = events->lod_level;
	g->render_config.use_depth_culling = events->use_depth_culling;
	g->render_config.fill_triangles = events->fill_triangles;
	clear_image(g);
	clear_z_buffer(g);
	draw_grid(g);
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->main_img.img, 0, 0);
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->gui_img.img, 0, 0);
	events->gui.fps = events->graphics->frame_data.fps;
	redraw_gui(events);
}

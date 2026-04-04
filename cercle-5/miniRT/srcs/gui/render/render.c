/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:49:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 08:50:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	gui_render(t_gui *gui)
{
	t_render	render;
	size_t		s;

	if (!gui || !gui->scene)
		return ;
	s = gui->render.scale;
	if (s < 1)
		s = 1;
	gui->win.size.x = gui->win.disp_size.x / (int)s;
	gui->win.size.y = gui->win.disp_size.y / (int)s;
	gui->win.line_len = gui->win.size.x * 4;
	gui->win.addr = (char *)gui->win.render_pixels;
	render.gui = gui;
	render.next_tile_id = 0;
	render.step = 1;
	render.tiles_count.x = (gui->win.size.x + TILE_SIZE - 1) / TILE_SIZE;
	render.tiles_count.y = (gui->win.size.y + TILE_SIZE - 1) / TILE_SIZE;
	render.total_tiles = render.tiles_count.x * render.tiles_count.y;
	render.transform = gui->scene->camera.transform;
	render.aspect_ratio = (double)gui->win.size.x / (double)gui->win.size.y;
	render.half_height = tan(gui->scene->camera.fov * 0.5 * 3.14159 / 180.0);
	render.half_width = render.half_height * render.aspect_ratio;
	gui->render.cur_cam = gui->scene->camera.transform;
	gui->render.cur_half_w = render.half_width;
	gui->render.cur_half_h = render.half_height;
	render_tiles_worker(&render);
}

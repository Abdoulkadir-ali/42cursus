/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:49:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:58:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	setup_render_size(t_gui *gui, size_t s)
{
	gui->win.size.x = gui->win.disp_size.x / (int)s;
	gui->win.size.y = gui->win.disp_size.y / (int)s;
	gui->win.line_len = gui->win.size.x * 4;
	gui->win.addr = (char *)gui->win.render_pixels;
}

static void	setup_render_geometry(t_gui *gui, t_render *r, t_raytracer_engine *rt)
{
	r->tiles_count.x = (gui->win.size.x + TILE_SIZE - 1) / TILE_SIZE;
	r->tiles_count.y = (gui->win.size.y + TILE_SIZE - 1) / TILE_SIZE;
	r->total_tiles = ((r->tiles_count.x + 3) / 4)
		* ((r->tiles_count.y + 3) / 4) * 16;
	r->transform = gui->render.snap_transform;
	r->aspect_ratio = (double)gui->win.size.x / (double)gui->win.size.y;
	if (gui->render.snap_fov == rt->cache.fov
		&& (size_t)gui->win.size.x == rt->cache.res.x
		&& (size_t)gui->win.size.y == rt->cache.res.y)
		r->half_height = rt->cache.half_h;
	else
	{
		r->half_height = tan(gui->render.snap_fov * 0.5 * 3.14159 / 180.0);
		rt->cache.half_h = r->half_height;
		rt->cache.fov = gui->render.snap_fov;
		rt->cache.res = vec2i((int)gui->win.size.x, (int)gui->win.size.y);
	}
	r->half_width = r->half_height * r->aspect_ratio;
	gui->render.cur_cam = gui->render.snap_transform;
	gui->render.cur_half_w = r->half_width;
	gui->render.cur_half_h = r->half_height;
}

static void	update_rt_stats(t_gui *gui, t_raytracer_engine *rt, long long start)
{
	rt->stats.last_render_ms = (double)(now_ms() - start);
	rt->stats.rays_frame = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	rt->stats.rays_total += rt->stats.rays_frame;
	rt->stats.frame_count++;
	ft_print_debug("[RENDER] done \xe2\x80\x94 %.1f ms  %llu Mrays total\n",
		rt->stats.last_render_ms,
		(unsigned long long)(rt->stats.rays_total / 1000000));
	fflush(stdout);
}

void	gui_render(t_gui *gui)
{
	t_render			render;
	t_raytracer_engine	*rt;
	size_t				s;
	long long			start;

	if (!gui || !gui->scene)
		return ;
	rt = &gui->rt_engine;
	s = gui->render.snap_scale;
	if (s < 1)
		s = 1;
	setup_render_size(gui, s);
	render.gui = gui;
	render.next_tile_id = 0;
	render.step = 1;
	setup_render_geometry(gui, &render, rt);
	ft_print_debug("[RENDER] scale=%zu size=%zux%zu tiles=%zux%zu total=%zu\n",
		s, gui->win.size.x, gui->win.size.y,
		render.tiles_count.x, render.tiles_count.y, render.total_tiles);
	fflush(stdout);
	start = now_ms();
	render_tiles_worker(&render);
	update_rt_stats(gui, rt, start);
}

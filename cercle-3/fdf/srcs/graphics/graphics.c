/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:25:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"
#include <pthread.h>

#define NUM_THREADS 4

static void	draw_horizontal_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_x;
	int		prev_x;

	DBG("draw_horizontal_line x=%d y=%d\n", x, y);
	next_x = x + step;
	if (next_x >= g->map->width || !is_point_visible(g->map->points[y][next_x],
			g))
		return ;
	p2 = project_point(g->map->points[y][next_x], g->camera,
			g->camera->projection, g->map->z_divisor);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_x = x - step;
		if (prev_x >= 0)
			p0 = project_point(g->map->points[y][prev_x], g->camera,
					g->camera->projection, g->map->z_divisor);
		else
			p0 = p1;
		if (next_x + step < g->map->width)
			p3 = project_point(g->map->points[y][next_x + step], g->camera,
					g->camera->projection, g->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(g, p0, p1, p2, p3, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static void	draw_vertical_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_y;
	int		prev_y;

	DBG("draw_vertical_line x=%d y=%d\n", x, y);
	next_y = y + step;
	if (next_y >= g->map->height || !is_point_visible(g->map->points[next_y][x],
			g))
		return ;
	p2 = project_point(g->map->points[next_y][x], g->camera,
			g->camera->projection, g->map->z_divisor);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_y = y - step;
		if (prev_y >= 0)
			p0 = project_point(g->map->points[prev_y][x], g->camera,
					g->camera->projection, g->map->z_divisor);
		else
			p0 = p1;
		if (next_y + step < g->map->height)
			p3 = project_point(g->map->points[next_y + step][x], g->camera,
					g->camera->projection, g->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(g, p0, p1, p2, p3, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;

	if (x + step >= g->map->width || y + step >= g->map->height)
		return ;
	p1 = project_point(g->map->points[y][x], g->camera, g->camera->projection,
			g->map->z_divisor);
	p2 = project_point(g->map->points[y][x + step], g->camera,
			g->camera->projection, g->map->z_divisor);
	p3 = project_point(g->map->points[y + step][x], g->camera,
			g->camera->projection, g->map->z_divisor);
	p4 = project_point(g->map->points[y + step][x + step], g->camera,
			g->camera->projection, g->map->z_divisor);
	draw_quad_triangles(g, p1, p2, p3, p4);
}

static void	draw_grid_section(t_graphics *g, int start_y, int end_y, int step)
{
	int		x;
	int		y;
	t_point	p1;

	DBG("draw_grid_section start y=%d to %d\n", start_y, end_y);
	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < g->map->width)
		{
			if (g->render_config.render_mode == RENDER_TRIANGLES)
			{
				draw_triangle_quad(g, x, y, step);
				x += step;
				continue ;
			}
			if (!is_point_visible(g->map->points[y][x], g))
			{
				x += step;
				continue ;
			}
			p1 = project_point(g->map->points[y][x], g->camera,
					g->camera->projection, g->map->z_divisor);
			draw_horizontal_line(g, x, y, p1, step);
			draw_vertical_line(g, x, y, p1, step);
			x += step;
		}
		y += step;
	}
	DBG("draw_grid_section end\n");
}

static void	*thread_draw(void *arg)
{
	t_thread_data	*td;

	td = (t_thread_data *)arg;
	draw_grid_section(td->g, td->start_y, td->end_y, td->step);
	return (NULL);
}

void	draw_grid(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				i;
	int				step;

	DBG("draw_grid start\n");
	step = g->render_config.lod_level;
	if (g->map->height < NUM_THREADS * 10)
	{
		DBG("draw_grid single thread\n");
		draw_grid_section(g, 0, g->map->height, step);
		DBG("draw_grid single thread done\n");
		return ;
	}
	DBG("draw_grid multi thread\n");
	rows_per_thread = g->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].g = g;
		thread_data[i].start_y = i * rows_per_thread;
		thread_data[i].step = step;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = g->map->height;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, thread_draw, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
	DBG("draw_grid multi thread done\n");
}

void	redraw(t_events *events)
{
	t_graphics			*g;
	t_camera_context	ctx;

	DBG("redraw start\n");
	g = events->graphics;
	g->map = events->map;
	g->camera = events->camera;
	g->render_config.render_mode = events->render_mode;
	g->render_config.lod_level = events->lod_level;
	g->render_config.use_depth_culling = events->use_depth_culling;
	g->render_config.fill_triangles = events->fill_triangles;
	ctx.camera = events->camera;
	ctx.map = g->map;
	ctx.window = events->window;
	update_zoom(&ctx);
	DBG("update_zoom done\n");
	clear_image(g);
	DBG("clear_image done\n");
	// clear_z_buffer(g);
	draw_grid(g);
	DBG("draw_grid done\n");
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->main_img.img, 0, 0);
	DBG("mlx_put_image main done\n");
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->gui_img.img, 0, 0);
	DBG("mlx_put_image gui done\n");
	render_gui(events->gui);
	DBG("render_gui done\n");
	DBG("redraw end\n");
}

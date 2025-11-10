/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"
#include "projection.h"
#include "spline.h"
#include "triangle.h"
#include <pthread.h>

#define NUM_THREADS 4

typedef struct s_thread_data
{
	t_data	*data;
	int		start_y;
	int		end_y;
	int		step;
}	t_thread_data;

static void	draw_horizontal_line(t_data *data, int x, int y, t_point p1, int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_x;
	int		prev_x;

	next_x = x + step;
	if (next_x >= data->map->width
		|| !is_point_visible(data->map->points[y][next_x], data))
		return ;
	p2 = project_point(data->map->points[y][next_x], data->camera,
			data->camera.projection, data->map->z_divisor);
	if (!should_draw_line(p1, p2, data))
		return ;
	if (data->render_mode == RENDER_SPLINES)
	{
		prev_x = x - step;
		if (prev_x >= 0)
			p0 = project_point(data->map->points[y][prev_x], data->camera,
					data->camera.projection, data->map->z_divisor);
		else
			p0 = p1;
		if (next_x + step < data->map->width)
			p3 = project_point(data->map->points[y][next_x + step],
					data->camera, data->camera.projection, data->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(data, p0, p1, p2, p3, data->camera.spline_segments);
	}
	else if (data->render_mode == RENDER_LINES)
		draw_line(data, p1, p2);
}

static void	draw_vertical_line(t_data *data, int x, int y, t_point p1, int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_y;
	int		prev_y;

	next_y = y + step;
	if (next_y >= data->map->height
		|| !is_point_visible(data->map->points[next_y][x], data))
		return ;
	p2 = project_point(data->map->points[next_y][x], data->camera,
			data->camera.projection, data->map->z_divisor);
	if (!should_draw_line(p1, p2, data))
		return ;
	if (data->render_mode == RENDER_SPLINES)
	{
		prev_y = y - step;
		if (prev_y >= 0)
			p0 = project_point(data->map->points[prev_y][x], data->camera,
					data->camera.projection, data->map->z_divisor);
		else
			p0 = p1;
		if (next_y + step < data->map->height)
			p3 = project_point(data->map->points[next_y + step][x],
					data->camera, data->camera.projection, data->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(data, p0, p1, p2, p3, data->camera.spline_segments);
	}
	else if (data->render_mode == RENDER_LINES)
		draw_line(data, p1, p2);
}

static void	draw_triangle_quad(t_data *data, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;

	if (x + step >= data->map->width || y + step >= data->map->height)
		return ;
	p1 = project_point(data->map->points[y][x], data->camera,
			data->camera.projection, data->map->z_divisor);
	p2 = project_point(data->map->points[y][x + step], data->camera,
			data->camera.projection, data->map->z_divisor);
	p3 = project_point(data->map->points[y + step][x], data->camera,
			data->camera.projection, data->map->z_divisor);
	p4 = project_point(data->map->points[y + step][x + step], data->camera,
			data->camera.projection, data->map->z_divisor);
	draw_quad_triangles(data, p1, p2, p3, p4);
}

static void	draw_grid_section(t_data *data, int start_y, int end_y, int step)
{
	int		x;
	int		y;
	t_point	p1;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->render_mode == RENDER_TRIANGLES)
			{
				draw_triangle_quad(data, x, y, step);
				x += step;
				continue ;
			}
			if (!is_point_visible(data->map->points[y][x], data))
			{
				x += step;
				continue ;
			}
			p1 = project_point(data->map->points[y][x], data->camera,
					data->camera.projection, data->map->z_divisor);
			draw_horizontal_line(data, x, y, p1, step);
			draw_vertical_line(data, x, y, p1, step);
			x += step;
		}
		y += step;
	}
}

static void	*thread_draw(void *arg)
{
	t_thread_data	*td;

	td = (t_thread_data *)arg;
	draw_grid_section(td->data, td->start_y, td->end_y, td->step);
	return (NULL);
}

void	draw_grid(t_data *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				i;
	int				step;

	step = data->lod_level;
	if (data->map->height < NUM_THREADS * 10)
	{
		draw_grid_section(data, 0, data->map->height, step);
		return ;
	}
	rows_per_thread = data->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].data = data;
		thread_data[i].start_y = i * rows_per_thread;
		thread_data[i].step = step;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = data->map->height;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, thread_draw, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
}

void	redraw(t_data *data)
{
	update_zoom(data);
	clear_image(data);
	clear_z_buffer(data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->gui_img, 0, 0);
	render_gui(data);
}

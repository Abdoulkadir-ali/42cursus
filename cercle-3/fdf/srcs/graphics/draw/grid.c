/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:36:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <pthread.h>

// Wrapper function for pthreads
void *thread_draw_routine(void *data)
{
    t_thread_data *d = (t_thread_data *)data;
    draw_grid_section(d->g, d->start_y, d->end_y, d->step);
    return (NULL);
}

void	draw_grid(t_graphics *g)
{
    pthread_t       threads[NUM_THREADS];
    t_thread_data   args[NUM_THREADS];
    int             step;
    int             i;
    int             h_step;

    step = g->render_config.lod_level;
    h_step = g->map->height / NUM_THREADS;
    i = 0;
    while (i < NUM_THREADS)
    {
        args[i].g = g;
        args[i].step = step;
        args[i].start_y = i * h_step;
        if (i == NUM_THREADS - 1)
            args[i].end_y = g->map->height;
        else
            args[i].end_y = (i + 1) * h_step;
        
        pthread_create(&threads[i], NULL, thread_draw_routine, &args[i]);
        i++;
    }
    
    // Wait for all to finish
    i = 0;
    while (i < NUM_THREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void	draw_horizontal_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_x;
	int		prev_x;

	next_x = x + step;
	if (next_x >= g->map->width)
		return ;
	/* retrieve projected point from cache */
	p2 = get_cached_proj(g, next_x, y);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_x = x - step;
		if (prev_x >= 0)
			p0 = get_cached_proj(g, prev_x, y);
		else
			p0 = p1;
		if (next_x + step < g->map->width)
			p3 = get_cached_proj(g, next_x + step, y);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

void	draw_vertical_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_y;
	int		prev_y;

	next_y = y + step;
	if (next_y >= g->map->height)
		return ;
	p2 = get_cached_proj(g, x, next_y);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_y = y - step;
		if (prev_y >= 0)
			p0 = get_cached_proj(g, x, prev_y);
		else
			p0 = p1;
		if (next_y + step < g->map->height)
			p3 = get_cached_proj(g, x, next_y + step);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;

	if (x + step >= g->map->width || y + step >= g->map->height)
		return ;
    p1 = get_cached_proj(g, x, y);
    p2 = get_cached_proj(g, x + step, y);
    p3 = get_cached_proj(g, x, y + step);
    p4 = get_cached_proj(g, x + step, y + step);
	draw_quad_triangles(g, (t_quad_triangle){p1, p2, p3, p4});
}

void draw_grid_section(t_graphics *g, int start_y, int end_y, int step)
{
	int		x;
	int		y;
	t_point	p1;

	/* debug prints removed */

	y = start_y;
	while (y < end_y)
	{
		/* debug prints removed */
		x = 0;
		while (x < g->map->width)
		{
			/* debug prints removed */
			/* debug prints removed */
			if (g->render_config.render_mode == RENDER_TRIANGLES)
			{
				draw_triangle_quad(g, x, y, step);
				x += step;
				continue ;
			}
			/* get the pre-projected point from cache */
			p1 = get_cached_proj(g, x, y);
			/* simple cull: continue if underlying 3D point is not in frustum */
			if (!is_point_visible(g->map->points.pos[y * g->map->width + x], g))
			{
				x += step;
				continue ;
			}
			draw_horizontal_line(g, x, y, p1, step);
			draw_vertical_line(g, x, y, p1, step);
			x += step;
		}
                y += step;
        }
        /* debug prints removed */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:16:55 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 17:48:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "graphics.h"

/* Helper to fetch valid projected point
** Returns 1 if valid and visible, 0 otherwise.
*/
static int	get_point(t_graphics *g, int x, int y, t_point *p)
{
	if (x < 0 || x >= (int)g->map->width || y < 0 || y >= (int)g->map->height)
		return (0);
	*p = get_cached_proj(g, x, y);
	if (p->pos.x <= BAD_VALUE) return (0);
	return (1);
}

/*
** Draws primitives relative to (x,y) in directions (dx, dy).
** This handles Lines, and Triangles.
** Step is the LOD stride.
*/
static void	draw_surface_primitive(t_graphics *g, int x, int y, int dx, int dy, t_thread_data *t)
{
	t_point	curr, h_next, v_next, diag;
	int		has_curr, has_h, has_v, has_diag;
    // Margin to catch lines entering the strip from slightly outside
    int margin = 50; 

	// 1. Fetch Current
	has_curr = get_point(g, x, y, &curr);
	if (!has_curr) return;

	// 2. Early Bounds Check (Optimization)
	// Only apply for filled/triangle modes. In wireframe, lines can cross the strip
	// even if the start point is outside, so we need to check both endpoints.
	if ((g->render_config.filled || g->render_config.render_mode == RENDER_TRIANGLES))
	{
		if ((int)curr.pos.x < (int)t->min_visible_x - margin 
			|| (int)curr.pos.x > (int)t->max_visible_x + margin)
			return ;
	}

	// 3. Fetch Neighbors (Lazy)
	has_h = get_point(g, x + dx, y, &h_next);
	has_v = get_point(g, x, y + dy, &v_next);
    
    // Diag only needed for Triangles
    has_diag = 0;
	if ((g->render_config.render_mode == RENDER_TRIANGLES || (g->render_config.render_mode == RENDER_LINES && g->render_config.filled)))
        has_diag = get_point(g, x + dx, y + dy, &diag);

	// 4. HORIZONTAL CONNECTION
	if (g->render_config.render_mode == RENDER_LINES && !g->render_config.filled)
	{
		if (dx != 0 && has_h)
		{
			if (!((curr.pos.x < t->min_visible_x && h_next.pos.x < t->min_visible_x) ||
					(curr.pos.x >= t->max_visible_x && h_next.pos.x >= t->max_visible_x)))
			{
				t_clipping_bounds bounds = {t->min_visible_x, t->max_visible_x};
				draw_line_clipped(g, curr, h_next, bounds);
			}
		}
	}

	// 5. VERTICAL CONNECTION
	if (g->render_config.render_mode == RENDER_LINES && !g->render_config.filled)
	{
		if (dy != 0 && has_v)
		{
			if (!((curr.pos.x < t->min_visible_x && v_next.pos.x < t->min_visible_x) ||
					(curr.pos.x >= t->max_visible_x && v_next.pos.x >= t->max_visible_x)))
			{
				t_clipping_bounds bounds = {t->min_visible_x, t->max_visible_x};
				draw_line_clipped(g, curr, v_next, bounds);
			}
		}
	}

	// 6. TRIANGLE / FILLED GRID
	if (g->render_config.render_mode == RENDER_TRIANGLES || (g->render_config.render_mode == RENDER_LINES && g->render_config.filled))
	{
		// Need quad?
		if (has_h && has_v)
			draw_triangle(g, curr, h_next, v_next);
		
		if (has_h && has_v && has_diag)
			draw_triangle(g, h_next, diag, v_next);
	}
}

// Helper struct for Peak
typedef struct s_grid_pos { int x; int y; } t_grid_pos;

static t_grid_pos	get_peak_indices(t_graphics *g)
{
	int		w = g->map->width;
	int		h = g->map->height;
	float	max_y = -1000000.0f;
	t_grid_pos	peak = {0, 0};
	t_point	p;

	int		xs[] = {0, w/2, w-1};
	int		ys[] = {0, h/2, h-1};
	int		xi, yi;

	yi = 0;
	while (yi < 3)
	{
		xi = 0;
		while (xi < 3)
		{
			p = get_cached_proj(g, xs[xi], ys[yi]);
			if (p.pos.y > max_y)
			{
				max_y = p.pos.y;
				peak.x = xs[xi];
				peak.y = ys[yi];
			}
			xi++;
		}
		yi++;
	}
	return (peak);
}

static void	*thread_raycast_routine(void *data)
{
	t_thread_data	*t = (t_thread_data *)data;
	t_graphics		*g = t->g;
	int				w = g->map->width;
	int				h = g->map->height;
	t_grid_pos		peak;

	peak = get_peak_indices(g);

	// Radiant Iteration:
	// Split into 4 loops to radiate from (peak.x, peak.y)
	// 1. Y: peak.y -> 0 (Down), X: peak.x -> 0 (Left)
	
	int y, x;
int step = (int)g->render_config.lod_value;
	if (step < 1) step = 1;

	// Upper Half (Top to Peak) - Actually Backwards?
	// We want to process closest Y first. Peak Y is max. 
	// So we start at Peak Y and go Down to 0.
	
	// Phase 1: Y from Peak down to 0
	y = peak.y;
	while (y >= 0)
	{
		// Phase 1a: X from Peak to 0 (Left)
		x = peak.x;
		while (x >= 0)
		{
			draw_surface_primitive(g, x, y, -step, -step, t);
			x -= step;
		}
		// Phase 1b: X from Peak+step to Width (Right)
		x = peak.x + step;
		while (x < w)
		{
			draw_surface_primitive(g, x, y, step, -step, t);
			x += step;
		}
		y -= step;
	}

	// Phase 2: Y from Peak+step to Height
	y = peak.y + step;
	while (y < h)
	{
		// Phase 2a: X from Peak to 0
		x = peak.x;
		while (x >= 0)
		{
			draw_surface_primitive(g, x, y, -step, step, t);
			x -= step;
		}
		// Phase 2b: X from Peak+step to Width
		x = peak.x + step;
		while (x < w)
		{
			draw_surface_primitive(g, x, y, step, step, t);
			x += step;
		}
		y += step;
	}
	return (NULL);
}

static void	draw_grid_raycast_threaded(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	int				i;
	size_t			strip_width;

	strip_width = g->window->width / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].min_visible_x = i * strip_width;
		if (i == NUM_THREADS - 1)
			args[i].max_visible_x = g->window->width;
		else
			args[i].max_visible_x = (i + 1) * strip_width;
		
		pthread_create(&threads[i], NULL, thread_raycast_routine, &args[i]);
		i++;
	}
	join_threads(threads);
}

static void	draw_grid_threaded(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	float			lod_value;
	int				i;
	int				h_step;

	lod_value = g->render_config.lod_value;
	h_step = g->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].lod_value = lod_value;
		args[i].start_y = i * h_step;
		if (i == NUM_THREADS - 1)
			args[i].end_y = g->map->height;
		else
			args[i].end_y = (i + 1) * h_step;
		pthread_create(&threads[i], NULL, thread_draw_routine, &args[i]);
		i++;
	}
	join_threads(threads);
}

void	draw_grid(t_graphics *g)
{
	if (g->render_config.use_horizon_culling)
		draw_grid_raycast_threaded(g);
	else
		draw_grid_threaded(g);
}

void	draw_grid_section(t_graphics *g, int start_y, int end_y, float lod_value)
{
	int	y;
	int step_int = (int)lod_value;
	if (step_int < 1) step_int = 1;

	y = start_y;
	while (y < end_y)
	{
		draw_grid_row(g, y, lod_value);
		y += step_int;
	}
}

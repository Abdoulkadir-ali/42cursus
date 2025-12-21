/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:24:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

static float	calculate_zoom_bias(float raw_log)
{
	if (raw_log > 0)
	{
		if (raw_log > 0.5f)
			return ((raw_log - 0.5f) * 2.0f);
		return (0.0f);
	}
	return (raw_log * 1.0f);
}

static int	calculate_adaptive_level(t_graphics *g)
{
	float	base_scale;
	float	ratio;
	float	base_pts;
	float	ideal;

	if (g->base_map->width > 0)
		base_scale = (float)g->window->width / (g->base_map->width * 1.5);
	else
		base_scale = 1.0f;
	if (base_scale < 0.0001f)
		base_scale = 0.0001f;
	ratio = g->camera->scale / base_scale;
	if (ratio < 0.0001f)
		ratio = 0.0001f;
	base_pts = (float)(g->base_map->width * g->base_map->height);
	if (base_pts < 1.0f)
		base_pts = 1.0f;
	ideal = (log2f((float)g->render_config.target_tesselation_points / base_pts)
			* 0.5f) + calculate_zoom_bias(log2f(ratio));
	return ((int)roundf(ideal));
}

static void	apply_tesselation(t_graphics *g, int level)
{
	t_vec2	min;
	t_vec2	max;

	g->render_config.use_tesselation = 1;
	g->render_config.tesselation_level = level;
	if (g->render_config.tesselation_level > MAX_DETAIL_LEVEL)
		g->render_config.tesselation_level = MAX_DETAIL_LEVEL;

	min = (t_vec2){0, 0};
	max = (t_vec2){g->base_map->width, g->base_map->height};
	get_visible_map_bounds(g, &min, &max);

	// Cache Check
	if (g->tesselated_map 
		&& g->render_config.last_tess_level == g->render_config.tesselation_level
		&& g->render_config.last_tess_min.x == min.x
		&& g->render_config.last_tess_min.y == min.y
		&& g->render_config.last_tess_max.x == max.x
		&& g->render_config.last_tess_max.y == max.y)
	{
		g->map = g->tesselated_map;
		return ;
	}

	if (g->tesselated_map)
		free_map(g->tesselated_map);
	
	g->tesselated_map = generate_tesselated_submap(g->base_map, min, max,
			g->render_config.tesselation_level);
	
	if (g->tesselated_map)
	{
		g->map = g->tesselated_map;
		// Update Cache
		g->render_config.last_tess_level = g->render_config.tesselation_level;
		g->render_config.last_tess_min = min;
		g->render_config.last_tess_max = max;
	}
	else
	{
		g->map = g->base_map;
		g->render_config.use_tesselation = 0;
		// Invalidate Cache
		g->render_config.last_tess_level = -100;
	}
}

static void	apply_lod(t_graphics *g, int level)
{
	int	step;

	step = 1 << abs(level);
	g->render_config.lod_value = (float)step;
	g->map = g->base_map;
	if (g->tesselated_map)
	{
		free_map(g->tesselated_map);
		g->tesselated_map = NULL;
	}
}

static void	geometry_processing(t_graphics *g)
{
	int	level;
	int	min_level_for_mode;

	// Filled surfaces look much better with tesselation
	// Automatically use higher detail for filled/triangle modes
	if (g->render_config.filled || g->render_config.render_mode == RENDER_TRIANGLES)
		min_level_for_mode = 2;  // At least 2 levels of tesselation for smooth fills
	else
		min_level_for_mode = MIN_DETAIL_LEVEL;

	if (g->render_config.use_adaptive_logic)
	{
		level = calculate_adaptive_level(g);
		if (level > MAX_DETAIL_LEVEL)
			level = MAX_DETAIL_LEVEL;
		if (level < min_level_for_mode)
			level = min_level_for_mode;
		g->render_config.detail_level = level;
	}
	level = g->render_config.detail_level;
	
	// Enforce minimum detail for filled modes even in manual mode
	if (level < min_level_for_mode)
	{
		level = min_level_for_mode;
		g->render_config.detail_level = level; // Update config so GUI shows correct level
	}
		
	g->render_config.use_tesselation = 0;
	g->render_config.lod_value = 1.0f;
	if (level > 0)
	{
		apply_tesselation(g, level);
		// Tesselated maps already have the detail baked in
		// Always use lod_value=1.0 to draw ALL cells without skipping
		g->render_config.lod_value = 1.0f;
	}
	else if (level < 0)
		apply_lod(g, level);
	else
	{
		g->map = g->base_map;
		if (g->tesselated_map)
		{
			free_map(g->tesselated_map);
			g->tesselated_map = NULL;
		}
	}
}
	
	
static void	rasterization(t_graphics *g)
{
	clear_frame_buffers(g);
	if (g->render_config.use_horizon_culling && g->horizon_buffer)
	{
		size_t i = 0;
		int height_val = (int)g->window->height;
		__m256i height_vec = _mm256_set1_epi32(height_val);
		while (i < g->window->width - 7)
		{
			_mm256_storeu_si256((__m256i *)&g->horizon_buffer[i], height_vec);
			i += 8;
		}
		while (i < g->window->width)
			g->horizon_buffer[i++] = height_val;
	}
	cache_projections(g);
	draw_grid(g);
}

void	render_scene(t_graphics *g)
{
	if (!g || !g->map || !g->camera)
		return ;
	if (!g->dirty)
		return ;
	if (!is_map_visible(g))
	{
		clear_frame_buffers(g);
		g->dirty = 0;
		return ;
	}
	geometry_processing(g);
	rasterization(g);
	g->dirty = 0;
}

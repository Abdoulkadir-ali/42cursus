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

static t_point	prepare_point(t_vec3d p3d, int color, t_camera *cam,
		double z_divisor)
{
	t_point	p;

	p.pos.x = p3d.x;
	p.pos.y = p3d.y;
	p.pos.z = p3d.z;
	p.color = color;
	if (cam->use_z_divisor && z_divisor != 0.0)
		p.pos.z /= z_divisor;
	p.pos.z *= cam->z_scale;
	return (p);
}

t_point	project_point(t_vec3d p3d, int color, t_camera *cam, double z_divisor)
{
	t_point	p;

	if (p3d.z <= BAD_VALUE + 1.0)
		return ((t_point){.pos = {BAD_VALUE, BAD_VALUE, BAD_VALUE},
			.color = color});
	p = prepare_point(p3d, color, cam, z_divisor);
	return (project_unified(p, cam));
}

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
	if (g->tesselated_map)
		free_map(g->tesselated_map);
	g->tesselated_map = generate_tesselated_submap(g->base_map, min, max,
			g->render_config.tesselation_level,
			g->render_config.max_tesselation_points);
	if (g->tesselated_map)
		g->map = g->tesselated_map;
	else
	{
		g->map = g->base_map;
		g->render_config.use_tesselation = 0;
	}
}

static void	apply_lod(t_graphics *g, int level)
{
	int	step;

	step = 1 << abs(level);
	g->render_config.lod_value = (float)step;
	g->render_config.detail_step = (float)step;
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

	if (g->render_config.use_adaptive_logic)
	{
		level = calculate_adaptive_level(g);
		if (level > MAX_DETAIL_LEVEL)
			level = MAX_DETAIL_LEVEL;
		if (level < MIN_DETAIL_LEVEL)
			level = MIN_DETAIL_LEVEL;
		g->render_config.detail_level = level;
	}
	level = g->render_config.detail_level;
	g->render_config.use_tesselation = 0;
	g->render_config.lod_value = 1.0f;
	g->render_config.detail_step = 1.0f;
	if (level > 0)
		apply_tesselation(g, level);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 15:24:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	cleanup_cache(t_graphics *g)
{
	if (g->cache.points)
	{
		free(g->cache.points);
		g->cache.points = NULL;
	}
	g->cache.width = 0;
	g->cache.height = 0;
	g->cache.map = NULL;
	g->cache.cache_valid = 0;
}

static int	camera_state_changed(t_graphics *g)
{
	return (g->cache.cam_state.position.x != g->camera->offset.x
		|| g->cache.cam_state.position.y != g->camera->offset.y
		|| g->cache.cam_state.rotation.x != g->camera->rotation.x
		|| g->cache.cam_state.rotation.y != g->camera->rotation.y
		|| g->cache.cam_state.rotation.z != g->camera->rotation.z
		|| g->cache.cam_state.scale != g->camera->scale
		|| g->cache.cam_state.z_scale_val != g->camera->z_scale
		|| g->cache.cam_state.alpha != g->camera->alpha);
}

void	cache_projections(t_graphics *g)
{
	if (!g || !g->map || !g->camera)
		return ;
	if (g->cache.cache_valid && g->cache.map == g->map
		&& !camera_state_changed(g))
		return ;
	update_rotation_matrix(g->camera);
	init_cache(g);
	if (g->cache.points)
	{
		calculate_transform_matrix(g->camera);
		fill_cache(g);
		g->cache.cam_state.position.x = g->camera->offset.x;
		g->cache.cam_state.position.y = g->camera->offset.y;
		g->cache.cam_state.rotation = g->camera->rotation;
		g->cache.cam_state.scale = g->camera->scale;
		g->cache.cam_state.z_scale_val = g->camera->z_scale;
		g->cache.cam_state.alpha = g->camera->alpha;
		g->cache.cache_valid = 1;
	}
}

t_point	get_fallback_proj(t_graphics *g, int x, int y)
{
	size_t	idx;
	t_point	bad_point;
	t_vec3d	p3d;
	t_point	p_in;

	idx = y * g->map->width + x;
	if (g->map->points.pos[idx].z <= BAD_VALUE + 1.0)
	{
		bad_point.pos.x = BAD_VALUE;
		bad_point.pos.y = BAD_VALUE;
		bad_point.pos.z = BAD_VALUE;
		bad_point.color = create_color(0, 0, 0);
		return (bad_point);
	}
	p3d = g->map->points.pos[idx];
	if (g->camera->use_z_divisor && g->map->z_divisor != 0.0)
		p3d.z /= g->map->z_divisor;
	p_in.pos = p3d;
	p_in.color = g->map->points.color[idx];
	return (apply_transform(p_in, g->camera));
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	int	valid;

	valid = x >= 0 && y >= 0 && (size_t)x < g->cache.width
		&& (size_t)y < g->cache.height;
	if (g->cache.points && g->cache.map == g->map && valid)
		return (g->cache.points[y * g->cache.width + x]);
	return (get_fallback_proj(g, x, y));
}

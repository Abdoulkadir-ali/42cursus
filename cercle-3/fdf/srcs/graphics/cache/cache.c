/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Release the projection cache and reset its metadata.
 * @param g Graphics state owning the cache.
 */
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

/**
 * @brief Check whether the cached camera state differs from the live camera.
 * @param g Graphics state owning the cache and camera.
 * @return Non-zero when the cache must be refreshed.
 */
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

/**
 * @brief Refresh cached point projections when the map or camera changed.
 * @param g Graphics state owning the cache, map, and camera.
 */
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

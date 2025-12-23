/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 14:56:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "gui.h"

static double	calculate_ideal_zoom(t_camera_manager *ctx)
{
	double	scale_x;
	double	scale_y;
	double	scale;
	int		max_dim;

	if (ctx->map->height > ctx->map->width)
		max_dim = ctx->map->height;
	else
		max_dim = ctx->map->width;
	scale_x = (ctx->window->width * DEFAULT_ZOOM_AVAILABLE_WIDTH)
		/ (max_dim * DEFAULT_ZOOM_PADDING);
	scale_y = (ctx->window->height * DEFAULT_ZOOM_AVAILABLE_HEIGHT)
		/ (max_dim * DEFAULT_ZOOM_PADDING);
	scale = scale_x;
	if (scale_y < scale)
		scale = scale_y;
	if (scale < DEFAULT_ZOOM_MIN)
		scale = DEFAULT_ZOOM_MIN;
	if (scale > DEFAULT_ZOOM_MAX)
		scale = DEFAULT_ZOOM_MAX;
	return (scale / 5.0);
}

static void	calculate_ideal_position(t_camera_manager *ctx)
{
	ctx->camera->offset.x = (ctx->window->width + GUI_PANEL_WIDTH) / 2.0;
	ctx->camera->offset.y = ctx->window->height / 2.0;
}

static void	set_ideal_angle(t_camera_manager *ctx)
{
	ctx->camera->rotation.x = 35.264;
	ctx->camera->rotation.y = 0.0;
	ctx->camera->rotation.z = 45.0;
}

void	adjust_camera_to_map(t_camera_manager *ctx)
{
	double	ideal_scale;

	if (!ctx || !ctx->map)
		return ;
	ideal_scale = calculate_ideal_zoom(ctx);
	ctx->camera->scale = ideal_scale;
	ctx->camera->target_scale = ideal_scale;
	set_ideal_angle(ctx);
	calculate_ideal_position(ctx);
	ctx->camera->grid_center.x = (ctx->map->width - 1) / 2.0;
	ctx->camera->grid_center.y = (ctx->map->height - 1) / 2.0;
	ctx->camera->grid_center.z = (ctx->map->min_max_z.x
			+ ctx->map->min_max_z.y) / 2.0;
	ctx->camera->dampening_threshold = 0.0;
	ctx->camera->alpha = 90.0;
}

void	center_camera_on_map(t_camera_manager *ctx)
{
	double	ideal_scale;

	if (!ctx || !ctx->map)
		return ;
	ctx->camera->grid_center.x = (ctx->map->width - 1) / 2.0;
	ctx->camera->grid_center.y = (ctx->map->height - 1) / 2.0;
	ctx->camera->grid_center.z = (ctx->map->min_max_z.x
			+ ctx->map->min_max_z.y) / 2.0;
	ideal_scale = calculate_ideal_zoom(ctx);
	ctx->camera->scale = ideal_scale;
	ctx->camera->target_scale = ideal_scale;
	ctx->camera->dampening_threshold = 0.0;
	ctx->camera->z_scale = 1.0;
	calculate_ideal_position(ctx);
}

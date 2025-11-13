/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 01:03:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static int	get_max_dimension(t_camera_context *ctx)
{
	if (ctx->map->height > ctx->map->width)
		return (ctx->map->height);
	return (ctx->map->width);
}

static double	calculate_ideal_zoom(t_camera_context *ctx)
{
	double	scale_x;
	double	scale_y;
	double	scale;
	int		max_dim;

	max_dim = get_max_dimension(ctx);
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
	return (scale);
}

static void	calculate_ideal_position(t_camera_context *ctx)
{
	double	y_adjust;

	y_adjust = (ctx->map->height * ctx->camera->scale)
		* DEFAULT_Y_ADJUST_FACTOR;
	ctx->camera->offset.x = ctx->window->width / 2.0;
	ctx->camera->offset.y = (ctx->window->height / 2.0) - y_adjust;
}

static void	set_ideal_angle(t_camera_context *ctx)
{
	ctx->camera->rotation.x = DEFAULT_CAMERA_ROTATION_X;
	ctx->camera->rotation.y = DEFAULT_CAMERA_ROTATION_Y;
	ctx->camera->rotation.z = DEFAULT_CAMERA_ROTATION_Z;
}

void	adjust_camera_to_map(t_camera_context *ctx)
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
	ctx->camera->grid_center.z = 0.0;
	ctx->camera->dampening_threshold = 0.0;
}

void	reset_style(t_camera *camera)
{
	if (!camera)
		return ;
	camera->color_shift.x = 0;
	camera->color_shift.y = 0;
	camera->color_shift.z = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 17:36:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static double	calculate_ideal_zoom(t_data *data)
{
	double	scale_x;
	double	scale_y;
	double	scale;
	int		max_dim;
	double	available_width;
	double	available_height;

	max_dim = data->map->width;
	if (data->map->height > max_dim)
		max_dim = data->map->height;
	available_width = data->win_width * DEFAULT_ZOOM_AVAILABLE_WIDTH;
	available_height = data->win_height * DEFAULT_ZOOM_AVAILABLE_HEIGHT;
	scale_x = available_width / (max_dim * DEFAULT_ZOOM_PADDING);
	scale_y = available_height / (max_dim * DEFAULT_ZOOM_PADDING);
	scale = scale_x;
	if (scale_y < scale)
		scale = scale_y;
	if (scale < DEFAULT_ZOOM_MIN)
		scale = DEFAULT_ZOOM_MIN;
	if (scale > DEFAULT_ZOOM_MAX)
		scale = DEFAULT_ZOOM_MAX;
	return (scale);
}

static void	calculate_ideal_position(t_data *data)
{
	double	y_adjust;

	y_adjust = (data->map->height * data->camera.scale)
		* DEFAULT_Y_ADJUST_FACTOR;
	data->camera.offset.x = data->win_width / 2.0;
	data->camera.offset.y = (data->win_height / 2.0) - y_adjust;
}

static void	set_ideal_angle(t_data *data)
{
	data->camera.rotation.x = DEFAULT_CAMERA_ROTATION_X;
	data->camera.rotation.y = DEFAULT_CAMERA_ROTATION_Y;
	data->camera.rotation.z = DEFAULT_CAMERA_ROTATION_Z;
}

void	adjust_camera_to_map(t_data *data)
{
	double	ideal_scale;

	if (!data || !data->map)
		return ;
	ideal_scale = calculate_ideal_zoom(data);
	data->camera.scale = ideal_scale;
	data->camera.target_scale = ideal_scale;
	set_ideal_angle(data);
	calculate_ideal_position(data);
	data->camera.color_shift.red = 0;
	data->camera.color_shift.blue = 0;
	data->camera.color_shift.green = 0;
	data->camera.dampening_threshold = 0.0;
}

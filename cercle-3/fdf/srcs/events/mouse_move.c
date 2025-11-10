/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 17:24:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_rotation(int x, int y, t_data *data)
{
	int	dx;
	int	dy;

	dx = x - data->mouse.last_x;
	dy = y - data->mouse.last_y;
	data->camera.rotation.y -= dx * 0.005;
	data->camera.rotation.x -= dy * 0.005;
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	redraw(data);
}

static void	clamp_color_shift(t_data *data)
{
	if (data->camera.color_shift.red > 255)
		data->camera.color_shift.red = 255;
	if (data->camera.color_shift.red < -255)
		data->camera.color_shift.red = -255;
	if (data->camera.color_shift.blue > 255)
		data->camera.color_shift.blue = 255;
	if (data->camera.color_shift.blue < -255)
		data->camera.color_shift.blue = -255;
	if (data->camera.color_shift.green > 255)
		data->camera.color_shift.green = 255;
	if (data->camera.color_shift.green < -255)
		data->camera.color_shift.green = -255;
}

static void	handle_color_shift(int x, int y, t_data *data)
{
	int	dx;
	int	dy;

	dx = x - data->mouse.last_x;
	dy = y - data->mouse.last_y;
	data->camera.color_shift.red += dx * 2;
	data->camera.color_shift.blue -= dx * 2;
	data->camera.color_shift.green -= dy * 2;
	clamp_color_shift(data);
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	redraw(data);
}

static void	handle_dampening(int x, int y, t_data *data)
{
	int		dx;
	int		dy;
	double	distance;
	double	max_relief;

	dx = x - data->mouse.middle_start_x;
	dy = y - data->mouse.middle_start_y;
	distance = sqrt(dx * dx + dy * dy);
	max_relief = (double)(data->map->max_z > -data->map->min_z
			? data->map->max_z : -data->map->min_z);
	if (max_relief < 1)
		max_relief = 1;
	data->camera.dampening_threshold = (distance / 200.0) * max_relief;
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	redraw(data);
}

int	mouse_move(int x, int y, t_data *data)
{
	if (data->mouse.left_pressed)
		handle_rotation(x, y, data);
	else if (data->mouse.right_pressed)
		handle_color_shift(x, y, data);
	else if (data->mouse.middle_pressed)
		handle_dampening(x, y, data);
	return (0);
}

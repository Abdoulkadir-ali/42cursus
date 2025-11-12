/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:59:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

static void	handle_object_vec3d(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->graphics->mouse.last_x;
	dy = y - events->graphics->mouse.last_y;
	factor = 0.005;
	events->camera->rotation.z -= dx * factor;
	events->camera->rotation.x -= dy * factor;
	events->graphics->mouse.last_x = x;
	events->graphics->mouse.last_y = y;
	redraw(events);
}

static void	handle_camera_rotation(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->graphics->mouse.last_x;
	dy = y - events->graphics->mouse.last_y;
	factor = 0.005;
	events->camera->rotation.z += dx * factor;
	events->camera->rotation.x += dy * factor;
	events->graphics->mouse.last_x = x;
	events->graphics->mouse.last_y = y;
	redraw(events);
}

static void	clamp_color_shift(t_events *events)
{
	if (events->camera->color_shift.x > 255)
		events->camera->color_shift.x = 255;
	if (events->camera->color_shift.x < -255)
		events->camera->color_shift.x = -255;
	if (events->camera->color_shift.z > 255)
		events->camera->color_shift.z = 255;
	if (events->camera->color_shift.z < -255)
		events->camera->color_shift.z = -255;
	if (events->camera->color_shift.y > 255)
		events->camera->color_shift.y = 255;
	if (events->camera->color_shift.y < -255)
		events->camera->color_shift.y = -255;
}

static void	handle_color_shift(int x, int y, t_events *events)
{
	int	dx;
	int	dy;

	dx = x - events->graphics->mouse.last_x;
	dy = y - events->graphics->mouse.last_y;
	events->camera->color_shift.x += dx * 2;
	events->camera->color_shift.z -= dx * 2;
	events->camera->color_shift.y -= dy * 2;
	clamp_color_shift(events);
	events->graphics->mouse.last_x = x;
	events->graphics->mouse.last_y = y;
	redraw(events);
}

static void	handle_dampening(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	distance;
	double	max_relief;

	dx = x - events->graphics->mouse.middle_start_x;
	dy = y - events->graphics->mouse.middle_start_y;
	distance = sqrt(dx * dx + dy * dy);
	if (events->map->max_z > -events->map->min_z)
		max_relief = (double)events->map->max_z;
	else
		max_relief = (double)(-events->map->min_z);
	if (max_relief < 1)
		max_relief = 1;
	events->camera->dampening_threshold = (distance / 200.0) * max_relief;
	events->graphics->mouse.last_x = x;
	events->graphics->mouse.last_y = y;
	redraw(events);
}

int	mouse_move(int x, int y, t_events *events)
{
	DBG("mouse_move: to %d,%d\n", x, y);
	if (events->graphics->keys.shift_left || events->graphics->keys.shift_right)
	{
		if (!events->graphics->mouse.middle_pressed)
		{
			events->graphics->mouse.middle_pressed = 1;
			events->graphics->mouse.middle_start_x = x;
			events->graphics->mouse.middle_start_y = y;
		}
		handle_dampening(x, y, events);
	}
	else if (events->graphics->mouse.middle_pressed)
		handle_color_shift(x, y, events);
	else if (events->graphics->mouse.right_pressed)
		handle_camera_rotation(x, y, events);
	else if (events->graphics->mouse.left_pressed)
		handle_object_vec3d(x, y, events);
	else
	{
		if (events->graphics->mouse.middle_pressed)
			events->graphics->mouse.middle_pressed = 0;
	}
	return (0);
}

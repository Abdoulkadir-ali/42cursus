/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:57:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	handle_object_vec3d(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->mouse.last_x;
	dy = y - events->mouse.last_y;
	factor = 0.005;
	events->camera->rotation.z -= dx * factor;
	events->camera->rotation.x -= dy * factor;
	update_rotation_matrix(events->camera);
	events->mouse.last_x = x;
	events->mouse.last_y = y;
	redraw(events);
}

static void	handle_camera_rotation(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->mouse.last_x;
	dy = y - events->mouse.last_y;
	factor = 0.005;
	events->camera->rotation.z += dx * factor;
	events->camera->rotation.x += dy * factor;
	update_rotation_matrix(events->camera);
	events->mouse.last_x = x;
	events->mouse.last_y = y;
	redraw(events);
}

static void	handle_color_shift(int x, int y, t_events *events)
{
	int	dx;
	int	dy;

	dx = x - events->mouse.last_x;
	dy = y - events->mouse.last_y;
	events->camera->color_shift.x += dx * 2;
	events->camera->color_shift.z -= dx * 2;
	events->camera->color_shift.y -= dy * 2;
	events->mouse.last_x = x;
	events->mouse.last_y = y;
	redraw(events);
}

static void	handle_dampening(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	distance;
	double	max_relief;

	dx = x - events->mouse.middle_start_x;
	dy = y - events->mouse.middle_start_y;
	distance = sqrt(dx * dx + dy * dy);
	if (events->map->min_max_z.y > -events->map->min_max_z.x)
		max_relief = (double)events->map->min_max_z.y;
	else
		max_relief = (double)(-events->map->min_max_z.x);
	if (max_relief < 1)
		max_relief = 1;
	events->camera->dampening_threshold = (distance / 200.0) * max_relief;
	events->mouse.last_x = x;
	events->mouse.last_y = y;
	redraw(events);
}

int	mouse_move(int x, int y, t_events *events)
{
	if (events->keys.shift_left || events->keys.shift_right)
	{
		if (!events->mouse.middle_pressed)
		{
			events->mouse.middle_pressed = 1;
			events->mouse.middle_start_x = x;
			events->mouse.middle_start_y = y;
		}
		handle_dampening(x, y, events);
	}
	else if (events->mouse.middle_pressed)
		handle_color_shift(x, y, events);
	else if (events->mouse.right_pressed)
		handle_camera_rotation(x, y, events);
	else if (events->mouse.left_pressed)
		handle_object_vec3d(x, y, events);
	else
	{
		if (events->mouse.middle_pressed)
			events->mouse.middle_pressed = 0;
	}
	return (0);
}

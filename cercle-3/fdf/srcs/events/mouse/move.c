/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Rotate the object-style target orientation from a left-drag gesture.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param events Event context owning the camera and mouse state.
 */
static void	handle_object_vec3d(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->mouse.last_x;
	dy = y - events->mouse.last_y;
	factor = 0.005;
	events->camera->target_rotation.z -= dx * factor;
	events->camera->target_rotation.x -= dy * factor;
	events->mouse.last_x = x;
	events->mouse.last_y = y;
}

/**
 * @brief Rotate the camera target orientation from a right-drag gesture.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param events Event context owning the camera and mouse state.
 */
static void	handle_camera_rotation(int x, int y, t_events *events)
{
	int		dx;
	int		dy;
	double	factor;

	dx = x - events->mouse.last_x;
	dy = y - events->mouse.last_y;
	factor = 0.005;
	events->camera->target_rotation.z += dx * factor;
	events->camera->target_rotation.x += dy * factor;
	events->mouse.last_x = x;
	events->mouse.last_y = y;
}

/**
 * @brief Adjust color-shift channels from a middle-drag gesture.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param events Event context owning the camera and mouse state.
 */
static void	handle_color_shift(int x, int y, t_events *events)
{
	t_vec2	delta;
	t_vec3	shift;

	delta.x = x - events->mouse.last_x;
	delta.y = y - events->mouse.last_y;
	shift.x = delta.x * 2;
	shift.y = -delta.y * 2;
	shift.z = -delta.x * 2;
	vec3_add(&events->camera->color_shift, shift);
	events->mouse.last_x = x;
	events->mouse.last_y = y;
	redraw(events);
}

/**
 * @brief Adjust dampening from the distance of a shift-drag gesture.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param events Event context owning the camera, map, and mouse state.
 */
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

/**
 * @brief Handle mouse motion gestures for rotation, color shift, and dampening.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param events Event context owning the active input state.
 * @return Always `0` for MLX callback compatibility.
 */
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

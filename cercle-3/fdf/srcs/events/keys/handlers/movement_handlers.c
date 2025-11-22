/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:04:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <math.h>
#include <stdio.h>

void	cycle_projection(t_events *events)
{
	events->camera->projection = (events->camera->projection + 1) % PROJ_COUNT;
}

void	reset_view(t_events *events)
{
	adjust_camera_to_map(events->camera_manager);
}

void	adjust_move_speed(t_events *events, int increase)
{
	if (increase)
	{
		events->camera->move_speed += 0.2;
		if (events->camera->move_speed > 5.0)
			events->camera->move_speed = 5.0;
	}
	else
	{
		events->camera->move_speed -= 0.2;
		if (events->camera->move_speed < 0.2)
			events->camera->move_speed = 0.2;
	}
}

int	process_movement(t_events *events)
{
	t_vec2d	v;
	int		m;
	double	speed;
	t_keys	*keyboard;
	t_vec2d	delta;
	double	max_off;

	v = create_vec2d(0, 0);
	keyboard = &events->keys;
	m = 1;
	if (events->camera->invert_movement)
		m = -1;
	speed = events->camera->move_speed;
	if (keyboard->up)
		vec2d_add(&v, create_vec2d(0, -1 * m));
	if (keyboard->down)
		vec2d_add(&v, create_vec2d(0, 1 * m));
	if (keyboard->left)
		vec2d_add(&v, create_vec2d(-1 * m, 0));
	if (keyboard->right)
		vec2d_add(&v, create_vec2d(1 * m, 0));
	if (v.x != 0 || v.y != 0)
	{
		vec2d_multiply_scalar(&v, speed);
		delta = v;
		vec2d_add(&events->camera->offset, delta);
		if (!isfinite(events->camera->offset.x)
			|| !isfinite(events->camera->offset.y))
		{
			events->camera->offset.x = 0.0;
			events->camera->offset.y = 0.0;
		}
		if (events->window)
		{
			max_off = (double)(events->window->width > events->window->height ? events->window->width : events->window->height)
				* 100.0;
			if (max_off > 500000.0)
				max_off = 500000.0;
			if (events->camera->offset.x > max_off)
				events->camera->offset.x = max_off;
			if (events->camera->offset.x < -max_off)
				events->camera->offset.x = -max_off;
			if (events->camera->offset.y > max_off)
				events->camera->offset.y = max_off;
			if (events->camera->offset.y < -max_off)
				events->camera->offset.y = -max_off;
		}
		return (1);
	}
	return (0);
}

int	handle_p(int keycode, t_events *events)
{
	(void)keycode;

	cycle_projection(events);
	return (1);
}
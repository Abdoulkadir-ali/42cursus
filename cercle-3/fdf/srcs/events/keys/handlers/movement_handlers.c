/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:09:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

void	cycle_projection(t_events *events)
{
	events->camera->projection = (events->camera->projection + 1) % PROJ_COUNT;
}

void	reset_view(t_events *events)
{
	t_camera_context	ctx;

	ctx.camera = events->camera;
	ctx.map = events->map;
	ctx.window = events->window;
	adjust_camera_to_map(&ctx);
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
		t_vec2d delta;

	v = create_vec2d(0, 0);
	keyboard = &events->graphics->keys;
	m = 1;
	if (events->camera->invert_movement)
		m = -1;
	speed = events->camera->move_speed;
	if (keyboard->up)
		v = v.add(v, create_vec2d(0, -1 * m));
	if (keyboard->down)
		v = v.add(v, create_vec2d(0, 1 * m));
	if (keyboard->left)
		v = v.add(v, create_vec2d(-1 * m, 0));
	if (keyboard->right)
		v = v.add(v, create_vec2d(1 * m, 0));
	if (v.x != 0 || v.y != 0)
	{
		delta = v.multiply_scalar(v, speed);
		DBG("process_movement: delta x=%.2f, y=%.2f\n", delta.x, delta.y);
		events->camera->offset = events->camera->offset.add(events->camera->offset,
				delta);
		return (1);
	}
	return (0);
}

int	handle_p(int keycode, t_events *events)
{
	(void)keycode;
	DBG("handle_p called\n");
	cycle_projection(events);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:28:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	cycle_projection(t_data *data)
{
	data->camera.projection = (data->camera.projection + 1) % PROJ_COUNT;
	redraw(data);
}

void	reset_view(t_data *data)
{
	t_camera_context	ctx;

	ctx.camera = &data->camera;
	ctx.map = data->map;
	ctx.window.width = data->win_width;
	ctx.window.height = data->win_height;
	adjust_camera_to_map(&ctx);
	redraw(data);
}

void	adjust_move_speed(t_data *data, int increase)
{
	if (increase)
	{
		data->camera.move_speed += 0.2;
		if (data->camera.move_speed > 5.0)
			data->camera.move_speed = 5.0;
	}
	else
	{
		data->camera.move_speed -= 0.2;
		if (data->camera.move_speed < 0.2)
			data->camera.move_speed = 0.2;
	}
	redraw(data);
}

void	process_movement(t_data *data)
{
	int		move_x;
	int		move_y;
	int		moved;
	double	speed;

	move_x = 0;
	move_y = 0;
	moved = 0;
	speed = data->camera.move_speed;
	if (data->camera.invert_movement)
	{
		if (data->keys.up)
			move_y += 1;
		if (data->keys.down)
			move_y -= 1;
		if (data->keys.left)
			move_x += 1;
		if (data->keys.right)
			move_x -= 1;
	}
	else
	{
		if (data->keys.up)
			move_y -= 1;
		if (data->keys.down)
			move_y += 1;
		if (data->keys.left)
			move_x -= 1;
		if (data->keys.right)
			move_x += 1;
	}
	if (move_x != 0 || move_y != 0)
	{
		data->camera.offset.x += move_x * 10 * speed;
		data->camera.offset.y += move_y * 10 * speed;
		moved = 1;
	}
	if (moved)
		redraw(data);
}

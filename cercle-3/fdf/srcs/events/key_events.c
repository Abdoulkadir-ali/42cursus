/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 15:51:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "projection.h"

static void	cycle_projection(t_data *data)
{
	data->camera.projection = (data->camera.projection + 1) % PROJ_COUNT;
	redraw(data);
}

static void	reset_view(t_data *data)
{
	data->camera.rotation.x = 0;
	data->camera.rotation.y = 0;
	data->camera.rotation.z = 0;
	data->camera.scale = 20;
	data->camera.target_scale = 20;
	data->camera.offset.x = data->win_width / 2;
	data->camera.offset.y = data->win_height / 2;
	data->camera.color_shift.red = 0;
	data->camera.color_shift.blue = 0;
	data->camera.color_shift.green = 0;
	redraw(data);
}

static void	adjust_move_speed(t_data *data, int increase)
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
	if (data->keys.up)
		move_y += 1;
	if (data->keys.down)
		move_y -= 1;
	if (data->keys.left)
		move_x += 1;
	if (data->keys.right)
		move_x -= 1;
	if (move_x != 0 || move_y != 0)
	{
		data->camera.offset.x += move_x * 10 * speed;
		data->camera.offset.y += move_y * 10 * speed;
		moved = 1;
	}
	if (moved)
		redraw(data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.esc)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	else if (keycode == data->buttons.keyboard.r)
		reset_view(data);
	else if (keycode == data->buttons.keyboard.p)
		cycle_projection(data);
	else if (keycode == data->buttons.keyboard.ctrl_left
		|| keycode == data->buttons.keyboard.ctrl_right)
	{
		if (keycode == data->buttons.keyboard.ctrl_left)
			data->keys.ctrl_left = 1;
		else
			data->keys.ctrl_right = 1;
	}
	else if (keycode == data->buttons.keyboard.up_arrow)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_move_speed(data, 1);
		else
			data->keys.up = 1;
	}
	else if (keycode == data->buttons.keyboard.down_arrow)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_move_speed(data, 0);
		else
			data->keys.down = 1;
	}
	else if (keycode == data->buttons.keyboard.left_arrow)
		data->keys.left = 1;
	else if (keycode == data->buttons.keyboard.right_arrow)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.up_arrow)
		data->keys.up = 0;
	else if (keycode == data->buttons.keyboard.down_arrow)
		data->keys.down = 0;
	else if (keycode == data->buttons.keyboard.left_arrow)
		data->keys.left = 0;
	else if (keycode == data->buttons.keyboard.right_arrow)
		data->keys.right = 0;
	else if (keycode == data->buttons.keyboard.ctrl_left)
		data->keys.ctrl_left = 0;
	else if (keycode == data->buttons.keyboard.ctrl_right)
		data->keys.ctrl_right = 0;
	return (0);
}

int	loop_hook(t_data *data)
{
	if (data->camera.scale != data->camera.target_scale)
		redraw(data);
	process_movement(data);
	return (0);
}

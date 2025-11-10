/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:55:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

static void	adjust_zoom_speed(t_data *data, int increase)
{
	if (increase)
	{
		data->camera.zoom_speed += 0.2;
		if (data->camera.zoom_speed > 5.0)
			data->camera.zoom_speed = 5.0;
	}
	else
	{
		data->camera.zoom_speed -= 0.2;
		if (data->camera.zoom_speed < 0.2)
			data->camera.zoom_speed = 0.2;
	}
	redraw(data);
}

static void	handle_mouse_click(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_LEFT)
	{
		data->mouse.left_pressed = 1;
		data->mouse.last_x = x;
		data->mouse.last_y = y;
	}
	else if (button == MOUSE_RIGHT)
	{
		data->mouse.right_pressed = 1;
		data->mouse.last_x = x;
		data->mouse.last_y = y;
	}
	else if (button == MOUSE_MIDDLE)
	{
		data->mouse.middle_pressed = 1;
		data->mouse.middle_start_x = x;
		data->mouse.middle_start_y = y;
		data->mouse.last_x = x;
		data->mouse.last_y = y;
	}
}

static void	handle_mouse_scroll(int button, t_data *data)
{
	if (button == MOUSE_SCROLL_UP)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_zoom_speed(data, 1);
		else
			zoom_in(data);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_zoom_speed(data, 0);
		else
			zoom_out(data);
	}
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	handle_mouse_click(button, x, y, data);
	handle_mouse_scroll(button, data);
	return (0);
}

int	mouse_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		data->mouse.left_pressed = 0;
	else if (button == MOUSE_RIGHT)
		data->mouse.right_pressed = 0;
	else if (button == MOUSE_MIDDLE)
		data->mouse.middle_pressed = 0;
	return (0);
}

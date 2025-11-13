/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:42:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

static int	adjust_zoom_speed(t_events *events, int increase)
{
	if (increase)
	{
		events->camera->zoom_speed += 0.2;
		if (events->camera->zoom_speed > 5.0)
			events->camera->zoom_speed = 5.0;
	}
	else
	{
		events->camera->zoom_speed -= 0.2;
		if (events->camera->zoom_speed < 0.2)
			events->camera->zoom_speed = 0.2;
	}
	return (1);
}

static void	handle_mouse_click(int button, int x, int y, t_mouse *mouse)
{
	if (button == MOUSE_LEFT)
	{
		mouse->left_pressed = 1;
		mouse->last_x = x;
		mouse->last_y = y;
	}
	else if (button == MOUSE_RIGHT)
	{
		mouse->right_pressed = 1;
		mouse->last_x = x;
		mouse->last_y = y;
	}
	else if (button == MOUSE_MIDDLE)
	{
		mouse->middle_pressed = 1;
		mouse->middle_start_x = x;
		mouse->middle_start_y = y;
		mouse->last_x = x;
		mouse->last_y = y;
	}
}

static int	handle_mouse_scroll(int button, t_events *events)
{
	if (button == MOUSE_SCROLL_UP)
	{
		if (events->keys.ctrl_left || events->keys.ctrl_right)
			return (adjust_zoom_speed(events, 1));
		else
			zoom_in(events->camera_ctx);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (events->keys.ctrl_left || events->keys.ctrl_right)
			return (adjust_zoom_speed(events, 0));
		else
			zoom_out(events->camera_ctx);
	}
	return (1);
}

static void	handle_mouse_release(int button, t_mouse *mouse)
{
	if (button == MOUSE_LEFT)
		mouse->left_pressed = 0;
	else if (button == MOUSE_RIGHT)
		mouse->right_pressed = 0;
	else if (button == MOUSE_MIDDLE)
		mouse->middle_pressed = 0;
}

int	mouse_press(int button, int x, int y, t_events *events)
{
	
	handle_mouse_click(button, x, y, &events->mouse);
	if (handle_mouse_scroll(button, events))
		redraw(events);
	return (0);
}

int	mouse_release(int button, int x, int y, t_events *events)
{
	
	(void)x;
	(void)y;
	handle_mouse_release(button, &events->mouse);
	return (0);
}

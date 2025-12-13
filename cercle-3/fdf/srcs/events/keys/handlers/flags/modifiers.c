/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:36:25 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:38:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_up(int keycode, t_events *events)
{
	t_keys	*keyboard;

	(void)keycode;
	keyboard = &events->keys;
	if (keyboard->ctrl_left || keyboard->ctrl_right)
	{
		adjust_move_speed(events, 1);
		return (1);
	}
	else
		keyboard->up = 1;
	return (0);
}

int	handle_down(int keycode, t_events *events)
{
	t_keys	*keyboard;

	(void)keycode;
	keyboard = &events->keys;
	if (keyboard->ctrl_left || keyboard->ctrl_right)
	{
		adjust_move_speed(events, 0);
		return (1);
	}
	else
		keyboard->down = 1;
	return (0);
}

int	handle_left(int keycode, t_events *events)
{
	return (handle_horizontal(keycode, events, 1));
}

int	handle_right(int keycode, t_events *events)
{
	return (handle_horizontal(keycode, events, 0));
}

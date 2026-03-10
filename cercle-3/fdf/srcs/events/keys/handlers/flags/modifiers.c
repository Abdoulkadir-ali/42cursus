/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:36:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Handle the up key, optionally increasing movement speed with Ctrl.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the key and camera state.
 * @return `1` for immediate speed changes, otherwise `0`.
 */
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

/**
 * @brief Handle the down key, optionally decreasing movement speed with Ctrl.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the key and camera state.
 * @return `1` for immediate speed changes, otherwise `0`.
 */
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

/**
 * @brief Mark the left-direction flag as pressed.
 * @param keycode Forwarded X11 keycode.
 * @param events Event context owning the key state.
 * @return `0` because movement is processed later from the loop hook.
 */
int	handle_left(int keycode, t_events *events)
{
	return (handle_horizontal(keycode, events, 1));
}

/**
 * @brief Mark the right-direction flag as pressed.
 * @param keycode Forwarded X11 keycode.
 * @param events Event context owning the key state.
 * @return `0` because movement is processed later from the loop hook.
 */
int	handle_right(int keycode, t_events *events)
{
	return (handle_horizontal(keycode, events, 0));
}

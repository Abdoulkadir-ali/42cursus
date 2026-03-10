/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Mark either the left or right directional flag as pressed.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the key state.
 * @param left Non-zero for left, zero for right.
 * @return Always `0` because movement is processed later.
 */
int	handle_horizontal(int keycode, t_events *events, int left)
{
	t_keys	*keyboard;

	(void)keycode;
	keyboard = &events->keys;
	if (left)
		keyboard->left = 1;
	else
		keyboard->right = 1;
	return (0);
}

/**
 * @brief Apply a press or release value to the tracked key flags.
 * @param keycode X11 keycode being processed.
 * @param events Event context owning the key state.
 * @param press Pressed state to assign.
 * @return Always `0` because flag changes are consumed later.
 */
static int	handle_flag(int keycode, t_events *events, int press)
{
	handle_button(keycode, events, press);
	return (0);
}

/**
 * @brief Mark a tracked key as pressed.
 * @param keycode X11 keycode being processed.
 * @param events Event context owning the key state.
 * @return Always `0` because flag changes are consumed later.
 */
int	handle_press_flag(int keycode, t_events *events)
{
	return (handle_flag(keycode, events, 1));
}

/**
 * @brief Mark a tracked key as released.
 * @param keycode X11 keycode being processed.
 * @param events Event context owning the key state.
 * @return Always `0` because flag changes are consumed later.
 */
int	handle_release_flag(int keycode, t_events *events)
{
	return (handle_flag(keycode, events, 0));
}

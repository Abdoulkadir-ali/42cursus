/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:55:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int	handle_up(int keycode, t_events *events)
{
	t_keys	*keyboard;

	(void)keycode;
	keyboard = &events->graphics->keys;
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
	keyboard = &events->graphics->keys;
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
	t_keys	*keyboard;

	(void)keycode;
	DBG("handle_left called\n");
	keyboard = &events->graphics->keys;
	keyboard->left = 1;
	return (0);
}

int	handle_right(int keycode, t_events *events)
{
	t_keys	*keyboard;

	(void)keycode;
	DBG("handle_right called\n");
	keyboard = &events->graphics->keys;
	keyboard->right = 1;
	return (0);
}

/* Generic button handler using map */
static int	*key_flag_ptrs[0x10000];

static void	init_key_flags(t_events *events)
{
	static int	initialized = 0;

	if (initialized)
		return ;
	initialized = 1;
	key_flag_ptrs[XK_Up] = &events->graphics->keys.up;
	key_flag_ptrs[XK_Down] = &events->graphics->keys.down;
	key_flag_ptrs[XK_Left] = &events->graphics->keys.left;
	key_flag_ptrs[XK_Right] = &events->graphics->keys.right;
	key_flag_ptrs[XK_Control_L] = &events->graphics->keys.ctrl_left;
	key_flag_ptrs[XK_Control_R] = &events->graphics->keys.ctrl_right;
	key_flag_ptrs[XK_Shift_L] = &events->graphics->keys.shift_left;
	key_flag_ptrs[XK_Shift_R] = &events->graphics->keys.shift_right;
	key_flag_ptrs[XK_l] = &events->graphics->keys.l;
	key_flag_ptrs[XK_L] = &events->graphics->keys.l;
	key_flag_ptrs[XK_z] = &events->graphics->keys.z;
	key_flag_ptrs[XK_Z] = &events->graphics->keys.z;
	key_flag_ptrs[XK_f] = &events->graphics->keys.f;
	key_flag_ptrs[XK_F] = &events->graphics->keys.f;
	key_flag_ptrs[XK_d] = &events->graphics->keys.d;
	key_flag_ptrs[XK_D] = &events->graphics->keys.d;
	key_flag_ptrs[XK_t] = &events->graphics->keys.t;
	key_flag_ptrs[XK_T] = &events->graphics->keys.t;
}

static void	handle_button(int keycode, t_events *events, int value)
{
	(void)events;
	if (keycode >= 0 && keycode < 0x10000 && key_flag_ptrs[keycode])
		*key_flag_ptrs[keycode] = value;
}

/* Unified flag handlers */
int	handle_press_flag(int keycode, t_events *events)
{
	init_key_flags(events);
	handle_button(keycode, events, 1);
	return (0);
}

int	handle_release_flag(int keycode, t_events *events)
{
	init_key_flags(events);
	handle_button(keycode, events, 0);
	return (0);
}
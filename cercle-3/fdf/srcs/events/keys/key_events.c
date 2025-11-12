/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:33:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>
#include <string.h>

#define KEY_MAP_SIZE 0x10000

static key_action_t	key_actions[KEY_MAP_SIZE];
static key_action_t	key_releases[KEY_MAP_SIZE];

static void	init_key_actions(void)
{
	static int	initialized = 0;

	if (initialized)
		return ;
	initialized = 1;
	ft_memset(key_actions, 0, sizeof(key_actions));
	ft_memset(key_releases, 0, sizeof(key_releases));
	key_actions[XK_Escape] = handle_escape;
	key_actions[XK_R] = handle_r;
	key_actions[XK_r] = handle_r;
	key_actions[XK_p] = handle_p;
	key_actions[XK_P] = handle_p;
	key_actions[XK_n] = handle_n;
	key_actions[XK_N] = handle_n;
	key_actions[XK_s] = handle_s;
	key_actions[XK_S] = handle_s;
	key_actions[XK_a] = handle_a;
	key_actions[XK_A] = handle_a;
	key_actions[XK_x] = handle_x;
	key_actions[XK_X] = handle_x;
	key_actions[XK_i] = handle_i;
	key_actions[XK_I] = handle_i;
	key_actions[XK_v] = handle_v;
	key_actions[XK_V] = handle_v;
	key_actions[XK_g] = handle_g;
	key_actions[XK_G] = handle_g;
	key_actions[XK_Control_L] = handle_press_flag;
	key_actions[XK_Control_R] = handle_press_flag;
	key_actions[XK_Shift_L] = handle_press_flag;
	key_actions[XK_Shift_R] = handle_press_flag;
	key_actions[XK_l] = handle_press_flag;
	key_actions[XK_L] = handle_press_flag;
	key_actions[XK_z] = handle_press_flag;
	key_actions[XK_Z] = handle_press_flag;
	key_actions[XK_f] = handle_press_flag;
	key_actions[XK_F] = handle_press_flag;
	key_actions[XK_d] = handle_press_flag;
	key_actions[XK_D] = handle_press_flag;
	key_actions[XK_t] = handle_press_flag;
	key_actions[XK_T] = handle_press_flag;
	key_actions[XK_plus] = handle_plus;
	key_actions[XK_minus] = handle_minus;
	key_actions[XK_0] = handle_0;
	key_actions[XK_Up] = handle_up;
	key_actions[XK_Down] = handle_down;
	key_actions[XK_Left] = handle_left;
	key_actions[XK_Right] = handle_right;
	key_releases[XK_Up] = handle_release_flag;
	key_releases[XK_Down] = handle_release_flag;
	key_releases[XK_Left] = handle_release_flag;
	key_releases[XK_Right] = handle_release_flag;
	key_releases[XK_Control_L] = handle_release_flag;
	key_releases[XK_Control_R] = handle_release_flag;
	key_releases[XK_Shift_L] = handle_release_flag;
	key_releases[XK_Shift_R] = handle_release_flag;
	key_releases[XK_l] = handle_release_flag;
	key_releases[XK_L] = handle_release_flag;
	key_releases[XK_z] = handle_release_flag;
	key_releases[XK_Z] = handle_release_flag;
	key_releases[XK_f] = handle_release_flag;
	key_releases[XK_F] = handle_release_flag;
	key_releases[XK_d] = handle_release_flag;
	key_releases[XK_D] = handle_release_flag;
	key_releases[XK_t] = handle_release_flag;
	key_releases[XK_T] = handle_release_flag;
}

int	key_press(int keycode, t_events *events)
{
	key_action_t	action;
	int				redraw_needed;

	init_key_actions();
	DBG("key_press: keycode %d\n", keycode);
	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = key_actions[keycode];
		if (action)
		{
			DBG("calling action for keycode %d\n", keycode);
			redraw_needed = action(keycode, events);
			// if (redraw_needed)
			// 	redraw(events);
			return (redraw_needed);
		}
		else
		{
			DBG("no action for keycode %d\n", keycode);
		}
	}
	return (0);
}

int	key_release(int keycode, t_events *events)
{
	key_action_t	action;

	init_key_actions();
	DBG("key_release: keycode %d\n", keycode);
	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = key_releases[keycode];
		if (action)
			return (action(keycode, events));
	}
	return (0);
}

int	loop_hook(t_events *events)
{
	static int	frame = 0;
	int	needs_redraw;

	DBG("loop_hook called, frame %d\n", frame);
	needs_redraw = 0;
	if (process_movement(events))
		needs_redraw = 1;
	needs_redraw++;
	if (frame % 10 == 0)
	{
		DBG("redrawing\n");
		redraw(events);
	}
	frame++;
	return (0);
}

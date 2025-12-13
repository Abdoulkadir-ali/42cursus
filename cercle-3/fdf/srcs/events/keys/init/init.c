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

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_key_actions(t_key_maps *key_maps)
{
	ft_memset(key_maps->key_actions, 0, sizeof(key_maps->key_actions));
	ft_memset(key_maps->key_releases, 0, sizeof(key_maps->key_releases));
	ft_memcpy(
		key_maps->key_actions,
		&(t_key_action[KEY_MAP_SIZE]){[XK_Escape] = handle_escape,
			[XK_R] = handle_r, [XK_r] = handle_r, [XK_p] = handle_p,
			[XK_P] = handle_p, [XK_n] = handle_n, [XK_N] = handle_n,
			[XK_s] = handle_s, [XK_S] = handle_s, [XK_a] = handle_a,
			[XK_A] = handle_a, [XK_x] = handle_x, [XK_X] = handle_x,
			[XK_i] = handle_i, [XK_I] = handle_i, [XK_v] = handle_v,
			[XK_V] = handle_v, [XK_g] = handle_g, [XK_G] = handle_g,
			[XK_Control_L] = handle_press_flag,
			[XK_Control_R] = handle_press_flag,
			[XK_Shift_L] = handle_press_flag, [XK_Shift_R] = handle_press_flag,
			[XK_l] = handle_press_flag, [XK_L] = handle_press_flag,
			[XK_z] = handle_press_flag, [XK_Z] = handle_press_flag,
			[XK_f] = handle_press_flag, [XK_F] = handle_press_flag,
			[XK_d] = handle_press_flag, [XK_D] = handle_press_flag,
			[XK_t] = handle_press_flag, [XK_T] = handle_press_flag,
			[XK_plus] = handle_plus, [XK_equal] = handle_plus,
			[XK_minus] = handle_minus, [XK_0] = handle_0, [XK_Up] = handle_up,
			[XK_Down] = handle_down, [XK_Left] = handle_left,
			[XK_Right] = handle_right},
		sizeof(key_maps->key_actions));
	ft_memcpy(key_maps->key_releases,
		&(t_key_action[KEY_MAP_SIZE]){[XK_Up] = handle_release_flag,
		[XK_Down] = handle_release_flag, [XK_Left] = handle_release_flag,
		[XK_Right] = handle_release_flag, [XK_Control_L] = handle_release_flag,
		[XK_Control_R] = handle_release_flag,
		[XK_Shift_L] = handle_release_flag, [XK_Shift_R] = handle_release_flag,
		[XK_l] = handle_release_flag, [XK_L] = handle_release_flag,
		[XK_z] = handle_release_flag, [XK_Z] = handle_release_flag,
		[XK_f] = handle_release_flag, [XK_F] = handle_release_flag,
		[XK_d] = handle_release_flag, [XK_D] = handle_release_flag,
		[XK_t] = handle_release_flag, [XK_T] = handle_release_flag},
		sizeof(key_maps->key_releases));
}

int	key_press(int keycode, t_events *events)
{
	t_key_action	action;
	int				redraw_needed;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_actions[keycode];
		if (action)
		{
			redraw_needed = action(keycode, events);
			if (redraw_needed)
				redraw(events);
			return (redraw_needed);
		}
	}
	return (0);
}

int	key_release(int keycode, t_events *events)
{
	t_key_action	action;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_releases[keycode];
		if (action)
			return (action(keycode, events));
	}
	return (0);
}

int	loop_hook(t_events *events)
{
	long			current_time;
	t_frame_data	*f;

	f = &events->graphics->frame_data;
	current_time = get_time_ms();
	if (f->last_check == 0)
		f->last_check = current_time;
	f->frame_count++;
	if (current_time - f->last_check >= 500)
	{
		f->fps = f->frame_count;
		f->frame_count = 0;
		f->last_check = current_time;
	}
	process_movement(events);
	redraw(events);
	return (0);
}

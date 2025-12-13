/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:27:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	set_arrows(int keycode, t_events *events, int value)
{
	if (keycode == XK_Up)
		events->keys.up = value;
	else if (keycode == XK_Down)
		events->keys.down = value;
	else if (keycode == XK_Left)
		events->keys.left = value;
	else if (keycode == XK_Right)
		events->keys.right = value;
}

static void	set_modifiers(int keycode, t_events *events, int value)
{
	if (keycode == XK_Control_L)
		events->keys.ctrl_left = value;
	else if (keycode == XK_Control_R)
		events->keys.ctrl_right = value;
	else if (keycode == XK_Shift_L)
		events->keys.shift_left = value;
	else if (keycode == XK_Shift_R)
		events->keys.shift_right = value;
}

static void	set_letters(int keycode, t_events *events, int value)
{
	if (keycode == XK_l || keycode == XK_L)
		events->keys.l = value;
	else if (keycode == XK_z || keycode == XK_Z)
		events->keys.z = value;
	else if (keycode == XK_f || keycode == XK_F)
		events->keys.f = value;
	else if (keycode == XK_d || keycode == XK_D)
		events->keys.d = value;
	else if (keycode == XK_t || keycode == XK_T)
		events->keys.t = value;
}

void	init_key_flags(t_events *events)
{
	(void)events;
}

void	handle_button(int keycode, t_events *events, int value)
{
	set_arrows(keycode, events, value);
	set_modifiers(keycode, events, value);
	set_letters(keycode, events, value);
}

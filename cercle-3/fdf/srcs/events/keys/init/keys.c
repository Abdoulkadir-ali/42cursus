/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:44:51 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	set_key_actions_1(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_Escape] = handle_escape;
	key_maps->key_actions[XK_R] = handle_r;
	key_maps->key_actions[XK_r] = handle_r;
	key_maps->key_actions[XK_p] = handle_p;
	key_maps->key_actions[XK_P] = handle_p;
	key_maps->key_actions[XK_n] = handle_n;
	key_maps->key_actions[XK_N] = handle_n;
	key_maps->key_actions[XK_s] = handle_s;
	key_maps->key_actions[XK_S] = handle_s;
	key_maps->key_actions[XK_a] = handle_a;
	key_maps->key_actions[XK_A] = handle_a;
}

static void	set_key_actions_2(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_x] = handle_x;
	key_maps->key_actions[XK_X] = handle_x;
	key_maps->key_actions[XK_i] = handle_i;
	key_maps->key_actions[XK_I] = handle_i;
	key_maps->key_actions[XK_v] = handle_v;
	key_maps->key_actions[XK_V] = handle_v;
	key_maps->key_actions[XK_g] = handle_g;
	key_maps->key_actions[XK_G] = handle_g;
	key_maps->key_actions[XK_Control_L] = handle_press_flag;
	key_maps->key_actions[XK_Control_R] = handle_press_flag;
}

static void	set_key_actions_3(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_Shift_L] = handle_press_flag;
	key_maps->key_actions[XK_Shift_R] = handle_press_flag;
	key_maps->key_actions[XK_l] = handle_press_flag;
	key_maps->key_actions[XK_L] = handle_press_flag;
	key_maps->key_actions[XK_z] = handle_press_flag;
	key_maps->key_actions[XK_Z] = handle_press_flag;
	key_maps->key_actions[XK_f] = handle_press_flag;
	key_maps->key_actions[XK_F] = handle_press_flag;
	key_maps->key_actions[XK_d] = handle_press_flag;
	key_maps->key_actions[XK_D] = handle_press_flag;
}

static void	set_key_actions_4(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_t] = handle_press_flag;
	key_maps->key_actions[XK_T] = handle_press_flag;
	key_maps->key_actions[XK_plus] = handle_plus;
	key_maps->key_actions[XK_equal] = handle_plus;
	key_maps->key_actions[XK_minus] = handle_minus;
	key_maps->key_actions[XK_0] = handle_0;
	key_maps->key_actions[XK_Up] = handle_up;
	key_maps->key_actions[XK_Down] = handle_down;
	key_maps->key_actions[XK_Left] = handle_left;
	key_maps->key_actions[XK_Right] = handle_right;
}

void	set_key_actions(t_key_maps *key_maps)
{
	set_key_actions_1(key_maps);
	set_key_actions_2(key_maps);
	set_key_actions_3(key_maps);
	set_key_actions_4(key_maps);
}

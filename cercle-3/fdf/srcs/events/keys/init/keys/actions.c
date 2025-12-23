/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:00:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	set_key_actions_1(t_key_maps *key_maps)
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
	key_maps->key_actions[XK_a] = handle_press_flag;
	key_maps->key_actions[XK_A] = handle_press_flag;
	key_maps->key_actions[XK_h] = handle_press_flag;
	key_maps->key_actions[XK_H] = handle_press_flag;
	key_maps->key_actions[XK_k] = handle_m;
	key_maps->key_actions[XK_K] = handle_m;
	key_maps->key_actions[XK_j] = handle_j;
	key_maps->key_actions[XK_J] = handle_j;
	key_maps->key_actions[XK_m] = handle_manual_mode;
	key_maps->key_actions[XK_M] = handle_manual_mode;
}

void	set_key_actions_2(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_x] = handle_press_flag;
	key_maps->key_actions[XK_X] = handle_press_flag;
	key_maps->key_releases[XK_x] = handle_release_flag;
	key_maps->key_releases[XK_X] = handle_release_flag;
	key_maps->key_actions[XK_y] = handle_press_flag;
	key_maps->key_actions[XK_Y] = handle_press_flag;
	key_maps->key_releases[XK_y] = handle_release_flag;
	key_maps->key_releases[XK_Y] = handle_release_flag;
	key_maps->key_actions[XK_i] = handle_i;
	key_maps->key_actions[XK_I] = handle_i;
	key_maps->key_actions[XK_v] = handle_v;
	key_maps->key_actions[XK_V] = handle_v;
	key_maps->key_actions[XK_g] = handle_g;
	key_maps->key_actions[XK_G] = handle_g;
	key_maps->key_actions[XK_w] = handle_press_flag;
	key_maps->key_actions[XK_W] = handle_press_flag;
	key_maps->key_actions[XK_Control_L] = handle_press_flag;
	key_maps->key_actions[XK_Control_R] = handle_press_flag;
}

void	set_key_actions_3(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_Shift_L] = handle_press_flag;
	key_maps->key_actions[XK_Shift_R] = handle_press_flag;
	key_maps->key_actions[XK_l] = handle_press_flag;
	key_maps->key_actions[XK_L] = handle_press_flag;
	key_maps->key_actions[XK_z] = handle_press_flag;
	key_maps->key_actions[XK_Z] = handle_press_flag;
	key_maps->key_releases[XK_z] = handle_release_flag;
	key_maps->key_releases[XK_Z] = handle_release_flag;
	key_maps->key_actions[XK_f] = handle_press_flag;
	key_maps->key_actions[XK_F] = handle_press_flag;
	key_maps->key_actions[KEY_B] = handle_press_flag;
	key_maps->key_releases[KEY_B] = handle_release_flag;
	key_maps->key_actions[XK_w] = handle_press_flag;
	key_maps->key_actions[XK_W] = handle_press_flag;
	key_maps->key_releases[XK_w] = handle_release_flag;
	key_maps->key_releases[XK_W] = handle_release_flag;
	key_maps->key_actions[XK_d] = handle_press_flag;
	key_maps->key_actions[XK_D] = handle_press_flag;
}

void	set_key_actions_4(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_t] = handle_t;
	key_maps->key_actions[XK_T] = handle_t;
	key_maps->key_actions[XK_Page_Up] = handle_tesselation_up;
	key_maps->key_actions[XK_Page_Down] = handle_tesselation_down;
	key_maps->key_actions[XK_Home] = handle_lod_up;
	key_maps->key_actions[XK_End] = handle_lod_down;
	key_maps->key_actions[XK_plus] = handle_plus;
	key_maps->key_actions[XK_equal] = handle_plus;
	key_maps->key_actions[XK_minus] = handle_minus;
	key_maps->key_actions[XK_0] = handle_0;
	key_maps->key_actions[XK_Up] = handle_up;
	key_maps->key_actions[XK_Down] = handle_down;
	key_maps->key_actions[XK_Left] = handle_left;
	key_maps->key_actions[XK_Right] = handle_right;
}

void	set_key_actions_5(t_key_maps *key_maps)
{
	key_maps->key_actions[XK_bracketleft] = handle_bracket;
	key_maps->key_actions[XK_bracketright] = handle_bracket;
	key_maps->key_actions[XK_comma] = handle_bracket;
	key_maps->key_actions[XK_period] = handle_bracket;
	key_maps->key_actions[XK_1] = handle_1;
	key_maps->key_actions[XK_2] = handle_2;
	key_maps->key_actions[XK_3] = handle_3;
	key_maps->key_actions[XK_q] = handle_1;
	key_maps->key_actions[XK_Q] = handle_1;
	key_maps->key_actions[XK_e] = handle_2;
	key_maps->key_actions[XK_E] = handle_2;
	key_maps->key_actions[XK_u] = handle_3;
	key_maps->key_actions[XK_U] = handle_3;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:15:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:45:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	set_input_movement(t_player_input *input, uint32_t action,
		int value)
{
	if (action == 0)
		input->move_forward = value;
	else if (action == 1)
		input->move_backward = value;
	else if (action == 2)
		input->strafe_left = value;
	else if (action == 3)
		input->strafe_right = value;
	else if (action == 4)
		input->rotate_left = value;
	else if (action == 5)
		input->rotate_right = value;
	else if (action == 6)
		input->pitch_up = value;
}

static void	set_input(t_player_input *input, uint32_t action, int value)
{
	if (action <= 6)
		set_input_movement(input, action, value);
	else if (action == 7)
		input->pitch_down = value;
	else if (action == 8)
		input->shoot = value;
	else if (action == 9)
		input->reload = value;
	else if (action == 10)
		input->sprint = value;
	else if (action == 11)
		input->crouch = value;
	else if (action == 12)
		input->interact = value;
	else if (action == 13)
		input->jump = value;
	else if (action >= 14 && action <= 16 && value)
		input->switch_weapon = (int)action - 13;
}

void	handle_key_press(int keycode, t_player_controller *controller)
{
	size_t			i;
	t_keymap_entry	*keymap;

	i = 0;
	keymap = get_keyboard_keymap();
	while (keymap[i].keycode != 0)
	{
		if (keymap[i].keycode == keycode)
		{
			set_input(&controller->input, keymap[i].flag, 1);
			break ;
		}
		i++;
	}
}

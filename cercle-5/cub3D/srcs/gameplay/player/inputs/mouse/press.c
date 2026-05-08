/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:17:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	handle_scroll(t_player_controller *ctrl, int button)
{
	if (button == 4)
	{
		ctrl->player->fov -= 2.0f;
		if (ctrl->player->fov < 30.0f)
			ctrl->player->fov = 30.0f;
	}
	else if (button == 5)
	{
		ctrl->player->fov += 2.0f;
		if (ctrl->player->fov > 120.0f)
			ctrl->player->fov = 120.0f;
	}
}

int	handle_mouse_press(int button, int x, int y, void *param)
{
	t_player_controller	*ctrl;

	ctrl = (t_player_controller *)param;
	if (button == 1)
	{
		ctrl->mouse.lmb_pressed = 1;
		ctrl->mouse.prev_x = x;
		ctrl->mouse.prev_y = y;
		ctrl->input.shoot = 1;
	}
	else
		handle_scroll(ctrl, button);
	return (0);
}

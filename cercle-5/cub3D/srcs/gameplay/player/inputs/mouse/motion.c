/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:21:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	apply_mouse_rotation(t_player_controller *ctrl, int dx, int dy)
{
	t_actor	*actor;
	float	nx;
	float	ny;
	float	rx;

	rx = -(float)dx * MOUSE_SENSITIVITY;
	actor = &ctrl->player->actor;
	nx = actor->dir.x * cosf(rx) - actor->dir.y * sinf(rx);
	ny = actor->dir.x * sinf(rx) + actor->dir.y * cosf(rx);
	actor->dir.x = nx;
	actor->dir.y = ny;
	ctrl->player->pitch_offset += (float)dy * PITCH_SENSITIVITY;
	if (ctrl->player->pitch_offset > MAX_PITCH)
		ctrl->player->pitch_offset = MAX_PITCH;
	if (ctrl->player->pitch_offset < -MAX_PITCH)
		ctrl->player->pitch_offset = -MAX_PITCH;
}

int	handle_mouse_motion(int x, int y, void *param)
{
	t_player_controller	*ctrl;

	ctrl = (t_player_controller *)param;
	if (ctrl->mouse.lmb_pressed == 0)
		return (0);
	apply_mouse_rotation(ctrl, ctrl->mouse.prev_x - x , ctrl->mouse.prev_y - y);
	ctrl->mouse.prev_x = x;
	ctrl->mouse.prev_y = y;
	return (0);
}

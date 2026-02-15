/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_strafe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	move_left_press(t_gui *gui)
{
	gui->cam_ctrl.moving_left = true;
}

void	move_left_release(t_gui *gui)
{
	gui->cam_ctrl.moving_left = false;
}

void	move_right_press(t_gui *gui)
{
	gui->cam_ctrl.moving_right = true;
}

void	move_right_release(t_gui *gui)
{
	gui->cam_ctrl.moving_right = false;
}

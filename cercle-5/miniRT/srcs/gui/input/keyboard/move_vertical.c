/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	move_up_press(t_gui *gui)
{
	gui->cam_ctrl.moving_up = true;
}

void	move_up_release(t_gui *gui)
{
	gui->cam_ctrl.moving_up = false;
}

void	move_down_press(t_gui *gui)
{
	gui->cam_ctrl.moving_down = true;
}

void	move_down_release(t_gui *gui)
{
	gui->cam_ctrl.moving_down = false;
}

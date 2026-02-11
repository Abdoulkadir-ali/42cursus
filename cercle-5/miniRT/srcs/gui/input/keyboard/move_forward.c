/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	move_forward_press(t_gui *gui)
{
	gui->cam_ctrl.moving_forward = true;
}

void	move_forward_release(t_gui *gui)
{
	gui->cam_ctrl.moving_forward = false;
}

void	move_backward_press(t_gui *gui)
{
	gui->cam_ctrl.moving_backward = true;
}

void	move_backward_release(t_gui *gui)
{
	gui->cam_ctrl.moving_backward = false;
}

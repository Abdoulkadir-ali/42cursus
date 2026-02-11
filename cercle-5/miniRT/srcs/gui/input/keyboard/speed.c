/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	speed_up_press(t_gui *gui)
{
	gui->cam_ctrl.move_speed += 0.1;
	if (gui->cam_ctrl.move_speed > 10.0)
		gui->cam_ctrl.move_speed = 10.0;
}

void	speed_down_press(t_gui *gui)
{
	gui->cam_ctrl.move_speed -= 0.1;
	if (gui->cam_ctrl.move_speed < 0.1)
		gui->cam_ctrl.move_speed = 0.1;
}

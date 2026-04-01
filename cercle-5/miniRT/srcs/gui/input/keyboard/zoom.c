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

#include "input.h"

void	zoom_in_press(t_gui *gui)
{
	gui->cam_ctrl.zooming_in = true;
}

void	zoom_in_release(t_gui *gui)
{
	gui->cam_ctrl.zooming_in = false;
}

void	zoom_out_press(t_gui *gui)
{
	gui->cam_ctrl.zooming_out = true;
}

void	zoom_out_release(t_gui *gui)
{
	gui->cam_ctrl.zooming_out = false;
}

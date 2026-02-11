/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	handle_scroll(int button, t_gui *gui)
{
	if (button == Button4)
	{
		gui->cam_ctrl.target_fov -= ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
	else if (button == Button5)
	{
		gui->cam_ctrl.target_fov += ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
}

int	mouse_click(int button, int x, int y, t_gui *gui)
{
	if (button == Button1)
	{
		gui->cam_ctrl.mouse_left_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else if (button == Button2)
	{
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else
		handle_scroll(button, gui);
	return (0);
}

int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == Button1)
		gui->cam_ctrl.mouse_left_pressed = false;
	else if (button == Button2)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}

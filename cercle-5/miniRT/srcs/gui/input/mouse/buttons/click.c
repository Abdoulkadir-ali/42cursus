/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:57:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	shoot_force(t_gui *gui, t_vec2i mouse);
void	handle_scroll(int b, t_gui *gui);

int	mouse_click(int button, t_vec2i mouse, t_gui *gui)
{
	widget_handle_mouse(gui, button, mouse);
	if (button == BUTTON_LEFT)
	{
		if (popup_handle_click(gui, mouse))
			return (0);
		if (!inspector_handle_click(gui, mouse)
			&& !scene_panel_handle_click(gui, mouse))
			pick_at_mouse(gui, mouse);
		if (!gui->slider_state.dragging)
			gui->cam_ctrl.mouse_left_pressed = true;
		gui->cam_ctrl.last_mouse = mouse;
	}
	else if (button == BUTTON_MIDDLE)
	{
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse = mouse;
	}
	else if (button == BUTTON_RIGHT)
		shoot_force(gui, mouse);
	else
		handle_scroll(button, gui);
	return (0);
}

int	mouse_release(int button, t_vec2i mouse, t_gui *gui)
{
	(void)mouse;
	if (button == BUTTON_LEFT)
	{
		end_inline_drag(gui);
		gui->cam_ctrl.mouse_left_pressed = false;
	}
	else if (button == BUTTON_MIDDLE)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}

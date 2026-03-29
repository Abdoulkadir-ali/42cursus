/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:17:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

int	mouse_click(int button, int x, int y, t_gui *gui)
{
	t_vec2i	mouse;

	mouse = vec2i(x, y);
	DBG_TRACE_MSG(DBG_CH_EDITOR, "mouse_click btn=%d (%d,%d)\n",
		button, x, y);
	widget_handle_mouse(gui, button, mouse);
	if (button == BUTTON_LEFT)
	{
		if (popup_handle_click(gui, mouse))
			return (0);
		if (!inspector_handle_click(gui, mouse)
			&& !scene_panel_handle_click(gui, mouse))
			pick_at_mouse(gui, mouse);
		if (!gui->slider_state->dragging)
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

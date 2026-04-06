/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 20:41:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "debug.h"

static void	handle_left_click(t_gui *gui, t_vec2i mouse)
{
	if (settings_handle_click(gui, mouse))
		return ;
	if (popup_handle_click(gui, mouse))
		return ;
	if (!inspector_handle_click(gui, mouse)
		&& !scene_panel_handle_click(gui, mouse))
		pick_at_mouse(gui, mouse);
	if (!gui->slider_state.dragging)
	{
		ft_print_debug("ROTATION START\n");
		gui->cam_ctrl.mouse_left_pressed = true;
	}
	gui->cam_ctrl.last_mouse = mouse;
}

int	mouse_click(int button, t_vec2i mouse, t_gui *gui)
{
	ft_print_debug("CLICK: btn=%d pos=%d,%d\n", button, mouse.x,
		mouse.y);
	widget_handle_mouse(gui, button, mouse);
	if (button == BUTTON_LEFT)
		handle_left_click(gui, mouse);
	else if (button == BUTTON_MIDDLE)
	{
		ft_print_debug("ZOOM START\n");
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse = mouse;
	}
	else if (button == BUTTON_RIGHT)
		shoot_force(gui, mouse);
	else
		handle_scroll(button, gui);
	return (0);
}

int	mouse_release(int button, t_gui *gui)
{
	ft_print_debug("RELEASE: btn=%d\n", button);
	if (button == BUTTON_LEFT)
	{
		widget_handle_release(gui);
		end_inline_drag(gui);
		settings_end_drag(gui);
		gui->cam_ctrl.mouse_left_pressed = false;
	}
	else if (button == BUTTON_MIDDLE)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}

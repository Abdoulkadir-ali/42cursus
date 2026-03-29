/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:16:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	end_inline_drag(t_gui *gui)
{
	gui->slider_state->dragging = false;
	gui->slider_state->prop = NULL;
	gui->slider_state->on_change = NULL;
	gui->slider_state->target = NULL;
}

int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
	{
		end_inline_drag(gui);
		gui->cam_ctrl.mouse_left_pressed = false;
	}
	else if (button == BUTTON_MIDDLE)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}

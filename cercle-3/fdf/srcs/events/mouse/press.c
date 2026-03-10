/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Handle a mouse press and trigger panel-button or scroll actions.
 * @param button Mouse button identifier.
 * @param x Mouse x position.
 * @param y Mouse y position.
 * @param events Event context owning the active input state.
 * @return Always `0` for MLX callback compatibility.
 */
int	mouse_press(int button, int x, int y, t_events *events)
{
	int	btn_y;

	handle_mouse_click(button, x, y, &events->mouse);
	btn_y = events->gui.window->height - 45;
	if (button == MOUSE_LEFT && x >= 15 && x <= (GUI_PANEL_WIDTH - 15)
		&& y >= btn_y && y <= btn_y + 30)
	{
		handle_g(0, events);
		return (0);
	}
	if (handle_mouse_scroll(button, events))
		redraw(events);
	return (0);
}

/**
 * @brief Handle a mouse release and clear the stored button state.
 * @param button Mouse button identifier.
 * @param x Unused mouse x position.
 * @param y Unused mouse y position.
 * @param events Event context owning the active input state.
 * @return Always `0` for MLX callback compatibility.
 */
int	mouse_release(int button, int x, int y, t_events *events)
{
	(void)x;
	(void)y;
	handle_mouse_release(button, &events->mouse);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:48:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Draw the X, Y, and Z labels around the axis indicator.
 * @param gui GUI object providing the window handle.
 * @param center Screen-space center of the indicator.
 */
void	draw_axis_labels(t_gui *gui, t_vec2 center)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + AXIS_SIZE
		+ 5, center.y - 5, 0xFF0000, "X");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + 5,
		center.y - AXIS_SIZE - 10, 0x00FF00, "Y");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + 5,
		center.y + 5, 0x0000FF, "Z");
}

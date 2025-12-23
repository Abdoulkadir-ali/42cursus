/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:19:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_axis_labels(t_gui *gui, t_vec2 center)
{
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + AXIS_SIZE
		+ 5, center.y - 5, 0xFF0000, "X");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + 5,
		center.y - AXIS_SIZE - 10, 0x00FF00, "Y");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr, center.x + 5,
		center.y + 5, 0x0000FF, "Z");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:48:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Draw one rotated axis line for the axis indicator overlay.
 * @param gui GUI object providing window and camera state.
 * @param center Screen-space center of the indicator.
 * @param axis Canonical axis vector to rotate.
 * @param color MLX color used for the line.
 */
void	draw_axis_line(t_gui *gui, t_vec2 center, t_vec3d axis, int color)
{
	t_vec3d	rotated;
	t_vec2	end_pos;
	t_vec2	current;

	rotated = apply_rotation_with_matrix(axis, gui->camera);
	end_pos.x = center.x + (int)(rotated.x * AXIS_SIZE);
	end_pos.y = center.y - (int)(rotated.y * AXIS_SIZE);
	current.x = center.x;
	current.y = center.y;
	while (current.x != end_pos.x || current.y != end_pos.y)
	{
		if (current.x >= 0 && current.x < (int)gui->window->width
			&& current.y >= 0 && current.y < (int)gui->window->height)
			mlx_pixel_put(gui->window->mlx_ptr, gui->window->ptr,
				(int)current.x, (int)current.y, color);
		if (current.x < end_pos.x)
			current.x++;
		else if (current.x > end_pos.x)
			current.x--;
		if (current.y < end_pos.y)
			current.y++;
		else if (current.y > end_pos.y)
			current.y--;
	}
}

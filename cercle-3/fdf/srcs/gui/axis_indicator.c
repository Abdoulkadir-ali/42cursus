/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_indicator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:03:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/22 12:17:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#define AXIS_SIZE 40
#define AXIS_MARGIN 20

static t_vec3d	rotate_axis_vec(t_vec3d v, t_camera *cam)
{
	return (apply_rotation_with_matrix(v, cam));
}

static void	draw_axis_line(t_gui *gui, t_vec2 center, t_vec3d axis, int color)
{
	t_vec3d	rotated;
	int		end_x;
	int		end_y;
	int		x;
	int		y;

	rotated = rotate_axis_vec(axis, gui->camera);
	end_x = center.x + (int)(rotated.x * AXIS_SIZE);
	end_y = center.y - (int)(rotated.y * AXIS_SIZE);
	x = center.x;
	y = center.y;
	while (x != end_x || y != end_y)
	{
		if (x >= 0 && x < (int)gui->window->width
			&& y >= 0 && y < (int)gui->window->height)
			mlx_pixel_put(gui->window->mlx_ptr, gui->window->ptr, x, y, color);
		if (x < end_x)
			x++;
		else if (x > end_x)
			x--;
		if (y < end_y)
			y++;
		else if (y > end_y)
			y--;
	}
}

void	draw_axis_indicator(t_gui *gui)
{
	t_vec2	center;
	t_vec3d	x_axis;
	t_vec3d	y_axis;
	t_vec3d	z_axis;

	if (!gui || !gui->window || !gui->camera)
		return ;
	center.x = gui->window->width - AXIS_SIZE - AXIS_MARGIN;
	center.y = gui->window->height - AXIS_SIZE - AXIS_MARGIN;
	x_axis = create_vec3d(1.0, 0.0, 0.0);
	y_axis = create_vec3d(0.0, 1.0, 0.0);
	z_axis = create_vec3d(0.0, 0.0, 1.0);
	draw_axis_line(gui, center, x_axis, 0xFF0000);
	draw_axis_line(gui, center, y_axis, 0x00FF00);
	draw_axis_line(gui, center, z_axis, 0x0000FF);
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr,
		center.x + AXIS_SIZE + 5, center.y - 5, 0xFF0000, "X");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr,
		center.x + 5, center.y - AXIS_SIZE - 10, 0x00FF00, "Y");
	mlx_string_put(gui->window->mlx_ptr, gui->window->ptr,
		center.x + 5, center.y + 5, 0x0000FF, "Z");
}

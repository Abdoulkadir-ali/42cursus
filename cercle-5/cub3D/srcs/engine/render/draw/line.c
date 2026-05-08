/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 04:09:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 19:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_vertical_line(t_window *win, int x, t_vec2 y_range, t_vec3 color)
{
	int	y;
	int	y_start;
	int	y_end;

	if (x < 0 || x >= win->width)
		return ;
	y_start = (int)y_range.x;
	y_end = (int)y_range.y;
	if (y_start > y_end)
	{
		y = y_start;
		y_start = y_end;
		y_end = y;
	}
	if (y_start < 0)
		y_start = 0;
	if (y_end >= win->height)
		y_end = win->height - 1;
	y = y_start;
	while (y <= y_end)
		put_pixel(win, (t_vec2){(float)x, (float)y++}, color);
}

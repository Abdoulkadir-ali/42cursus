/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 04:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:32:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	draw_sphere_dot(t_window *win, t_vec2 sp, int off, t_vec3 color)
{
	int	x;
	int	y;

	x = -off;
	while (x <= off)
	{
		y = -off;
		while (y <= off)
		{
			draw_debug_pixel(win, (t_vec2i){(int)sp.x + x, (int)sp.y + y},
				1.0f, color);
			y++;
		}
		x++;
	}
}

void	draw_debug_sphere(t_window *win, t_world *world, t_debug_shape *shape)
{
	t_vec2	sp;
	int		off;

	sp = project_to_screen(win, world, shape->p1);
	if (sp.x == -1)
		return ;
	off = 1;
	if (shape->radius > 0.5f)
	{
		off = (int)shape->radius;
		if (off < 1)
			off = 1;
		if (off > 3)
			off = 3;
	}
	draw_sphere_dot(win, sp, off, shape->color);
}
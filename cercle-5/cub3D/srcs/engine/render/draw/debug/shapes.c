/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:53:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"
#include <math.h>

void	add_debug_sphere(t_world *world, t_vec3 pos, float radius,
		t_dbg_style style)
{
	int	i;

	i = 0;
	while (i < MAX_DEBUG_SHAPES)
	{
		if (!world->debug_shapes[i].active)
		{
			world->debug_shapes[i].type = DEBUG_SPHERE;
			world->debug_shapes[i].p1 = pos;
			world->debug_shapes[i].radius = radius;
			world->debug_shapes[i].color = style.color;
			world->debug_shapes[i].lifetime_us = style.lifetime_ms * 1000;
			world->debug_shapes[i].active = true;
			return ;
		}
		i++;
	}
}

void	add_debug_box(t_world *world, t_vec3 min, t_vec3 max, t_dbg_style style)
{
	int	i;

	i = 0;
	while (i < MAX_DEBUG_SHAPES)
	{
		if (!world->debug_shapes[i].active)
		{
			world->debug_shapes[i].type = DEBUG_BOX;
			world->debug_shapes[i].p1 = min;
			world->debug_shapes[i].p2 = max;
			world->debug_shapes[i].color = style.color;
			world->debug_shapes[i].lifetime_us = style.lifetime_ms * 1000;
			world->debug_shapes[i].active = true;
			return ;
		}
		i++;
	}
}

void	add_debug_arrow(t_world *world, t_vec3 s, t_vec3 e, t_dbg_style style)
{
	int	i;

	i = 0;
	while (i < MAX_DEBUG_SHAPES)
	{
		if (!world->debug_shapes[i].active)
		{
			world->debug_shapes[i].type = DEBUG_ARROW;
			world->debug_shapes[i].p1 = s;
			world->debug_shapes[i].p2 = e;
			world->debug_shapes[i].color = style.color;
			world->debug_shapes[i].lifetime_us = style.lifetime_ms * 1000;
			world->debug_shapes[i].active = true;
			return ;
		}
		i++;
	}
}

void	update_debug_shapes(t_world *world, int elapsed_us)
{
	int	i;

	i = 0;
	while (i < MAX_DEBUG_SHAPES)
	{
		if (world->debug_shapes[i].active)
		{
			world->debug_shapes[i].lifetime_us -= elapsed_us;
			if (world->debug_shapes[i].lifetime_us <= 0)
				world->debug_shapes[i].active = false;
		}
		i++;
	}
}

void	draw_debug_line(t_window *win, t_vec2 p1, t_vec2 p2, t_vec3 color)
{
	t_vec2	delta;
	t_vec2	curr;
	float	steps;
	float	i;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	if (fabsf(delta.x) > fabsf(delta.y))
		steps = fabsf(delta.x);
	else
		steps = fabsf(delta.y);
	if (steps < 1.0f)
		return ;
	delta.x /= steps;
	delta.y /= steps;
	curr = p1;
	i = 0;
	while (i <= steps)
	{
		draw_debug_pixel(win, (t_vec2i){(int)curr.x, (int)curr.y}, 1.0f, color);
		curr.x += delta.x;
		curr.y += delta.y;
		i++;
	}
}

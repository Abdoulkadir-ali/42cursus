/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:37:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_vec3	tile_color(char c)
{
	if (c == '1')
		return (v3_col(COL_MM_WALL));
	if (c == '2')
		return (v3_col(COL_MM_DOOR));
	if (c == 'O')
		return (v3_col(COL_MM_OPEN_DOOR));
	if (c == '0')
		return (v3_col(COL_MM_FLOOR));
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

static void	draw_tile(t_window *win, t_world *world, t_vec2i p, t_vec2i start)
{
	char	c;
	t_vec2	pos;

	if (start.y + p.y < (int)world->map->size.y
		&& start.x + p.x < (int)world->map->size.x)
	{
		c = world->map->grid[start.y + p.y][start.x + p.x];
		if (c != ' ' && c != '\0')
		{
			pos.x = (float)win->mm_margin + (float)p.x
				* (float)win->mm_cell;
			pos.y = (float)win->mm_margin + (float)p.y
				* (float)win->mm_cell;
			draw_square(win, pos, (float)win->mm_cell - 1.0f,
				tile_color(c));
		}
	}
}

void	draw_minimap_grid(t_window *win, t_world *world, t_vec2i start,
	int view_size)
{
	int		y;
	int		x;

	y = -1;
	while (++y < view_size)
	{
		x = -1;
		while (++x < view_size)
			draw_tile(win, world, (t_vec2i){x, y}, start);
	}
}

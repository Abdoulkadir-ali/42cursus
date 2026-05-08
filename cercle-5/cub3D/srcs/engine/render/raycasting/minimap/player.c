/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:37:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	draw_player_icon(t_window *win, t_vec2 base)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 5)
				put_pixel(win, (t_vec2){base.x + (float)i,
					base.y + (float)j}, v3_col(COL_MM_PLAYER));
			j++;
		}
		i++;
	}
}

void	draw_player_arrow(t_window *win, t_world *world,
	int start_x, int start_y)
{
	t_vec2	base;
	t_vec3	dir;
	int		i;

	base.x = (float)win->mm_margin + (world->player.render_pos.x
			- (float)start_x) * (float)win->mm_cell;
	base.y = (float)win->mm_margin + (world->player.render_pos.y
			- (float)start_y) * (float)win->mm_cell;
	dir = world->player.render_dir;
	draw_player_icon(win, base);
	i = 0;
	while (i <= win->mm_cell * 2)
	{
		put_pixel(win, (t_vec2){base.x + dir.x * (float)i,
			base.y + dir.y * (float)i}, v3_col(COL_MM_DIR));
		i++;
	}
}

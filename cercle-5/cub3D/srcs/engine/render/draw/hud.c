/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 15:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	draw_rect(t_window *win, t_vec2i p, t_vec2i size, int color)
{
	int			i;
	int			j;
	int			cur_x;
	int			cur_y;
	uint32_t	*dst;

	i = -1;
	while (++i < size.y)
	{
		j = -1;
		while (++j < size.x)
		{
			cur_x = p.x + j;
			cur_y = p.y + i;
			if (cur_x >= 0 && cur_x < win->width && cur_y >= 0
				&& cur_y < win->height)
			{
				dst = (uint32_t *)(win->addr + cur_y * win->line_len) + cur_x;
				*dst = color;
			}
		}
	}
}

static void	draw_bar(t_window *win, t_vec2i p, t_vec2i val_max, t_vec2i colors)
{
	int	w[2];
	int	h;

	w[0] = 200;
	h = 20;
	w[1] = (int)((float)val_max.x / (float)val_max.y * (float)w[0]);
	if (w[1] > w[0])
		w[1] = w[0];
	if (w[1] < 0)
		w[1] = 0;
	draw_rect(win, (t_vec2i){p.x - 2, p.y - 2}, (t_vec2i){w[0] + 4, h + 4}, 0);
	draw_rect(win, p, (t_vec2i){w[0], h}, colors.y);
	draw_rect(win, p, (t_vec2i){w[1], h}, colors.x);
}

void	render_hud(t_window *win, t_world *world)
{
	int	margin;
	int	bar_y;

	margin = 40;
	bar_y = win->height - margin - 20;
	draw_bar(win, (t_vec2i){margin, bar_y},
		(t_vec2i){world->player.health, 100},
		(t_vec2i){0x00FF3232, 0x004B0000});
	if (world->player.armor > 0)
	{
		bar_y -= 30;
		draw_bar(win, (t_vec2i){margin, bar_y},
			(t_vec2i){world->player.armor, 100},
			(t_vec2i){0x0032FFFF, 0x00004B4B});
	}
}

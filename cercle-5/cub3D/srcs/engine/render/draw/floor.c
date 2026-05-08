/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:08:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"
#include "optimization.h"
#include <math.h>

static t_vec2	calc_floor_pos(t_window *win, t_world *world, int x, float p)
{
	float	fov_rad;
	float	plane_len;
	float	rd;
	t_vec2	rp;
	t_vec2	f;

	fov_rad = world->player.fov * M_PI / 360.0f;
	plane_len = tanf(fov_rad);
	rp.x = -world->player.render_dir.y * plane_len;
	rp.y = world->player.render_dir.x * plane_len;
	rd = (win->height * 0.5f * (0.66f / plane_len)) / p;
	f.x = world->player.render_pos.x + rd * (world->player.render_dir.x
			+ rp.x * (2.0f * x / (float)win->width - 1.0f));
	f.y = world->player.render_pos.y + rd * (world->player.render_dir.y
			+ rp.y * (2.0f * x / (float)win->width - 1.0f));
	return (f);
}

static void	draw_f_pix(t_window *win, t_world *world, int x, int y)
{
	float		p;
	t_vec2		f;
	t_vec2i		tx;
	t_texture	*ftex;

	p = (float)y - ((float)win->height / 2.0f
			- (world->player.render_pitch_offset * (float)win->height));
	if (fabsf(p) < 0.001f)
		return ;
	f = calc_floor_pos(win, world, x, p);
	ftex = &world->map->textures[TEX_FLOOR];
	if (!ftex->data || ftex->size.x == 0 || ftex->size.y == 0)
		return ;
	tx.x = (int)(f.x * (float)ftex->size.x) % (int)ftex->size.x;
	tx.y = (int)(f.y * (float)ftex->size.y) % (int)ftex->size.y;
	if (tx.x < 0)
		tx.x += (int)ftex->size.x;
	if (tx.y < 0)
		tx.y += (int)ftex->size.y;
	put_pixel(win, (t_vec2){(float)x, (float)y},
		get_tex_color(ftex, (t_vec2i){tx.x, tx.y}));
}

void	render_floor(t_window *win, t_world *world)
{
	int	y;
	int	x;
	int	hor;

	hor = (int)((float)win->height / 2.0f - (world->player.render_pitch_offset
				* (float)win->height));
	y = hor + 1;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			draw_f_pix(win, world, x, y);
			x++;
		}
		y++;
	}
}

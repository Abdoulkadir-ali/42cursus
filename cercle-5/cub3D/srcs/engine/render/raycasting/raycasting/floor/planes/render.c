/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:35:04 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:04:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	sample_and_draw(t_draw_line_data *d, t_window *win, int y)
{
	int			x;
	t_vec2		curr;
	uint32_t	pix;

	x = 0;
	while (x < win->width)
	{
		curr.x = d->floor_pos.x + d->floor_step.x * (float)x;
		curr.y = d->floor_pos.y + d->floor_step.y * (float)x;
		d->tx.x = (int)(curr.x * (float)d->tex->size.x) % d->tex->size.x;
		d->tx.y = (int)(curr.y * (float)d->tex->size.y) % d->tex->size.y;
		if (d->tx.x < 0)
			d->tx.x += d->tex->size.x;
		if (d->tx.y < 0)
			d->tx.y += d->tex->size.y;
		pix = d->tex->data[d->tx.y * d->tex->size.x + d->tx.x];
		d->line[x] = pix;
		if (win->z_buffer)
			win->z_buffer[y * win->width + x] = d->dist;
		x++;
	}
}

void	draw_plane_line(t_window *win, t_world *world, int y,
		t_draw_line_data *d)
{
	prepare_line_data(d, win, &d->player_ref, y);
	if (fabsf(d->p) < 0.0001f)
		return ;
	d->tex = &world->map->textures[TEX_CEIL];
	if (d->is_floor)
		d->tex = &world->map->textures[TEX_FLOOR];
	if (!d->tex->data || d->tex->size.x == 0 || d->tex->size.y == 0)
		return ;
	d->line = (uint32_t *)(win->addr + (size_t)y * win->line_len);
	sample_and_draw(d, win, y);
}

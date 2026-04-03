/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:31:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	process_tile_row(t_render *render, t_tile *v)
{
	v->p_pos.x = v->tile.x;
	v->pixel_ptr = v->row_ptr;
	while (v->p_pos.x < v->tile.x + TILE_SIZE
		&& v->p_pos.x < render->gui->win.size.x)
	{
		process_pixel(render, vec2i(v->p_pos.x, v->p_pos.y), v->pixel_ptr);
		v->p_pos.x += render->step;
		v->pixel_ptr += v->bpp_step;
	}
}

void	render_tile(t_render *render, size_t id)
{
	t_tile	v;

	v.tile.x = (id % render->tiles_count.x) * TILE_SIZE;
	v.tile.y = (id / render->tiles_count.x) * TILE_SIZE;
	v.p_pos.y = v.tile.y;
	v.row_ptr = render->gui->win.addr + (v.p_pos.y * render->gui->win.line_len)
		+ (v.tile.x * (render->gui->win.bpp / 8));
	v.bpp_step = (render->gui->win.bpp / 8) * render->step;
	v.row_step = render->gui->win.line_len * render->step;
	while (v.p_pos.y < v.tile.y + TILE_SIZE
		&& v.p_pos.y < render->gui->win.size.y)
	{
		process_tile_row(render, &v);
		v.p_pos.y += render->step;
		v.row_ptr += v.row_step;
	}
}

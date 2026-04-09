/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:50:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static const uint8_t	g_z4[16][2] = {
{0, 0}, {1, 0}, {0, 1}, {1, 1},
{2, 0}, {3, 0}, {2, 1}, {3, 1},
{0, 2}, {1, 2}, {0, 3}, {1, 3},
{2, 2}, {3, 2}, {2, 3}, {3, 3}
};

static bool	decode_morton(t_render *r, size_t id, t_vec2i *out)
{
	size_t	bk_x;
	size_t	bid;
	size_t	lid;

	bk_x = (r->tiles_count.x + 3) / 4;
	bid = id / 16;
	lid = id % 16;
	out->x = (bid % bk_x) * 4 + g_z4[lid][0];
	out->y = (bid / bk_x) * 4 + g_z4[lid][1];
	return (out->x < r->tiles_count.x && out->y < r->tiles_count.y);
}

static void	render_tile_row(t_render *render, t_tile *v, size_t id, int *cnt)
{
	long long	st;
	int			sw;

	sw = render->gui->win.size.x;
	st = now_ms();
	v->p_pos.x = v->tile.x;
	v->pixel_ptr = v->row_ptr;
	while (v->p_pos.x < v->tile.x + TILE_SIZE && v->p_pos.x < sw)
	{
		process_pixel(render, vec2i(v->p_pos.x, v->p_pos.y), v->pixel_ptr);
		v->p_pos.x += render->step;
		v->pixel_ptr += v->bpp_step;
	}
	if (id == 0)
	{
		ft_print_debug("[TILE 0] Row %d done in %lld ms\n", (*cnt)++,
			now_ms() - st);
		fflush(stdout);
	}
}

void	render_tile(t_render *render, size_t id)
{
	t_tile	v;
	int		cnt;
	int		sh;

	sh = render->gui->win.size.y;
	if (!decode_morton(render, id, &v.tile))
		return ;
	v.tile.x *= TILE_SIZE;
	v.tile.y *= TILE_SIZE;
	v.p_pos.y = v.tile.y;
	v.row_ptr = render->gui->win.addr + (v.p_pos.y * render->gui->win.line_len)
		+ (v.tile.x * (render->gui->win.bpp / 8));
	v.bpp_step = (render->gui->win.bpp / 8) * render->step;
	v.row_step = render->gui->win.line_len * render->step;
	cnt = 0;
	while (v.p_pos.y < v.tile.y + TILE_SIZE && v.p_pos.y < sh)
	{
		render_tile_row(render, &v, id, &cnt);
		v.p_pos.y += render->step;
		v.row_ptr += v.row_step;
	}
}

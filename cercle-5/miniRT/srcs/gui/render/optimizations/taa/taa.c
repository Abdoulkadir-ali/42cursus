/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 03:10:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Halton low-discrepancy sequence for sub-pixel jitter.
** base 2 for x, base 3 for y — standard TAA choice.
*/

static uint32_t	blend_taa(uint32_t cur, uint32_t hist)
{
	t_vec3i	c;
	t_vec3i	h;
	int		a;
	int		b;

	a = (int)(TAA_ALPHA * 256.0f);
	b = 256 - a;
	c = rt_unpack_color_v(cur);
	h = rt_unpack_color_v(hist);
	c.x = (a * c.x + b * h.x) >> 8;
	c.y = (a * c.y + b * h.y) >> 8;
	c.z = (a * c.z + b * h.z) >> 8;
	return (rt_pack_color_v(c));
}

void	taa_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	t_vec2i			out;
	t_vec2i			d;
	uint32_t		cur;

	o = &gui->opts;
	d.y = y_start;
	while (d.y < y_end)
	{
		d.x = 0;
		while (d.x < gui->win.size.x)
		{
			cur = gui->win.addr[d.y * gui->win.size.x + d.x];
			if (o->prev_valid && reproject_taa(gui, d.x, d.y, &out))
				o->taa_buf[d.y * gui->win.size.x + d.x] = blend_taa(cur,
						o->prev_color[out.y * o->prev_render_size.x + out.x]);
			else
				o->taa_buf[d.y * gui->win.size.x + d.x] = cur;
			d.x++;
		}
		d.y++;
	}
}

/*
** Entry: dispatches parallel TAA accumulation, then copies taa_buf
** back into the render buffer so the rest of the pipeline sees it.
*/
void	taa_apply(t_gui *gui)
{
	size_t	n;

	if (!gui->opts.taa_buf || !gui->opts.depth_buf)
		return ;
	gui->opts.taa_frame++;
	gui_parallel_task_worker(gui, TASK_TAA);
	n = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	ft_memcpy(gui->win.addr, gui->opts.taa_buf, n * sizeof(uint32_t));
}

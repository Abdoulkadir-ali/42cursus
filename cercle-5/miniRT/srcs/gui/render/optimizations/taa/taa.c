/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Halton low-discrepancy sequence for sub-pixel jitter.
** base 2 for x, base 3 for y — standard TAA choice.
*/

static size_t	blend_taa(size_t cur, size_t hist)
{
	t_vec3i	c;
	t_vec3i	h;
	int		a;
	int		b;

	a = (TAA_ALPHA * 256.0f);
	b = 256 - a;
	c = rt_unpack_color_v(cur);
	h = rt_unpack_color_v(hist);
	c.x = (a * c.x + b * h.x) >> 8;
	c.y = (a * c.y + b * h.y) >> 8;
	c.z = (a * c.z + b * h.z) >> 8;
	return (rt_pack_color_v(c));
}

static void	taa_pixel(t_gui *gui, t_optimizations *o, t_vec2i d)
{
	t_vec2i		out;
	size_t		cur;
	uint32_t	*pixels;
	int			sw;

	sw = gui->win.size.x;
	pixels = (uint32_t *)gui->win.addr;
	cur = pixels[d.y * sw + d.x];
	if (o->prev_valid && reproject_taa(gui, d.x, d.y, &out))
		o->taa_buf[d.y * sw + d.x] = blend_taa(cur,
				o->prev_color[out.y * o->prev_render_size.x + out.x]);
	else
		o->taa_buf[d.y * sw + d.x] = cur;
}

void	taa_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	t_vec2i			d;
	int				sw;

	o = &gui->opts;
	sw = gui->win.size.x;
	d.y = y_start;
	while (d.y < (int)y_end)
	{
		d.x = 0;
		while (d.x < sw)
		{
			taa_pixel(gui, o, d);
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
	n = gui->win.size.x * gui->win.size.y;
	ft_memcpy(gui->win.addr, gui->opts.taa_buf, n * sizeof(uint32_t));
}

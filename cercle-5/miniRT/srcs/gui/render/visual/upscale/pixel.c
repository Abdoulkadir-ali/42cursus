/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 14:52:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	upscale_pix_exec(t_gui *gui, t_vec2i dst, size_t c[4],
	t_vec4f w)
{
	uint32_t	*out;
	size_t		off;

	off = dst.y * gui->win.disp_line_len;
	out = (uint32_t *)(gui->win.disp_addrs[gui->render.back_idx] + off);
	out[dst.x] = (uint32_t)bilerp_pixel(c, w);
}

void	upscale_pixel(t_gui *gui, t_vec2i dst, t_vec2 src)
{
	t_vec4f		w;
	uint32_t	*rows[2];
	float		*depths[2];
	size_t		colors[4];
	t_vec2i		p;
	size_t		dx;

	dx = gui->win.size.x;
	p.x = src.x;
	p.y = src.y;
	rows[0] = (uint32_t *)gui->win.addr + dx * p.y;
	rows[1] = rows[0] + dx;
	if (gui->opts.depth_buf)
	{
		depths[0] = gui->opts.depth_buf + dx * p.y + p.x;
		depths[1] = depths[0] + dx;
	}
	else
	{
		depths[0] = NULL;
		depths[1] = NULL;
	}
	get_weights(&w, (t_vec2f){(float)(src.x - p.x), (float)(src.y - p.y)}, depths);
	colors[0] = rows[0][p.x];
	colors[1] = rows[0][p.x + 1];
	colors[2] = rows[1][p.x];
	colors[3] = rows[1][p.x + 1];
	upscale_pix_exec(gui, dst, colors, w);
}

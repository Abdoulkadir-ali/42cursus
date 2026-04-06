/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	upscale_pix_exec(t_gui *gui, t_vec2i dxy, uint32_t c[4],
	float w[4])
{
	uint32_t	*out;
	size_t		off;

	off = (size_t)dxy.y * gui->win.disp_line_len;
	out = (uint32_t *)(gui->win.disp_addrs[gui->render.back_idx] + off);
	out[dxy.x] = bilerp_pixel(c, w);
}

void	upscale_pixel(t_gui *gui, t_vec2i dxy, t_vec2 rxy, size_t d[2])
{
	float		w[4];
	uint32_t	*rows[2];
	float		*depths[2];
	uint32_t	colors[4];
	t_vec2i		p;

	p.x = (int)rxy.x;
	p.y = (int)rxy.y;
	rows[0] = (uint32_t *)gui->win.addr + (size_t)d[0] * (size_t)p.y;
	rows[1] = rows[0] + d[0];
	depths[0] = gui->opts.depth_buf + (size_t)d[0] * (size_t)p.y + p.x;
	depths[1] = depths[0] + d[0];
	get_weights(w, (float)(rxy.x - p.x), (float)(rxy.y - p.y), depths);
	colors[0] = rows[0][p.x];
	colors[1] = rows[0][p.x + 1];
	colors[2] = rows[1][p.x];
	colors[3] = rows[1][p.x + 1];
	upscale_pix_exec(gui, dxy, colors, w);
}

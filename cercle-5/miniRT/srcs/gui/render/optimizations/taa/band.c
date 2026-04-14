/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa_band.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 03:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <math.h>

static uint32_t	apply_clamp(t_vec3i h, t_vec3i mn, t_vec3i mx)
{
	int	m[3];
	int	e[3];

	m[0] = (mn.x + mx.x) >> 1;
	m[1] = (mn.y + mx.y) >> 1;
	m[2] = (mn.z + mx.z) >> 1;
	e[0] = (int)(((mx.x - mn.x) * TAA_CLAMP_EXPAND) * 0.5f) + 1;
	e[1] = (int)(((mx.y - mn.y) * TAA_CLAMP_EXPAND) * 0.5f) + 1;
	e[2] = (int)(((mx.z - mn.z) * TAA_CLAMP_EXPAND) * 0.5f) + 1;
	if (h.x < m[0] - e[0])
		h.x = m[0] - e[0];
	else if (h.x > m[0] + e[0])
		h.x = m[0] + e[0];
	if (h.y < m[1] - e[1])
		h.y = m[1] - e[1];
	else if (h.y > m[1] + e[1])
		h.y = m[1] + e[1];
	if (h.z < m[2] - e[2])
		h.z = m[2] - e[2];
	else if (h.z > m[2] + e[2])
		h.z = m[2] + e[2];
	return (rt_pack_color_v(h));
}

static void	sample_neighbor(t_vec3i *m, t_vec3i s)
{
	if (s.x < m[0].x)
		m[0].x = s.x;
	if (s.y < m[0].y)
		m[0].y = s.y;
	if (s.z < m[0].z)
		m[0].z = s.z;
	if (s.x > m[1].x)
		m[1].x = s.x;
	if (s.y > m[1].y)
		m[1].y = s.y;
	if (s.z > m[1].z)
		m[1].z = s.z;
}

static void	clamp_hist(t_gui *gui, t_vec2i d, uint32_t *hist)
{
	t_vec3i		m[2];
	t_vec2i		n;
	uint32_t	*src;

	src = (uint32_t *)gui->win.addr;
	m[0] = rt_unpack_color_v(src[d.y * gui->win.size.x + d.x]);
	m[1] = m[0];
	n.y = -2;
	while (++n.y <= 1)
	{
		n.x = -2;
		while (++n.x <= 1)
		{
			if (d.x + n.x >= 0 && d.x + n.x < (int)gui->win.size.x
				&& d.y + n.y >= 0 && d.y + n.y < (int)gui->win.size.y)
				sample_neighbor(m, rt_unpack_color_v(src[(d.y + n.y)
						* gui->win.size.x + (d.x + n.x)]));
		}
	}
	*hist = apply_clamp(rt_unpack_color_v(*hist), m[0], m[1]);
}

static void	taa_p(t_gui *gui, t_optimizations *opts, t_vec2i d, t_vec2i *o)
{
	t_vec3i		c[2];
	const int	a = (int)(TAA_ALPHA * 256);
	uint32_t	hist;
	t_vec2		jc;
	t_vec2		jp;

	if (fabs(opts->cur_cam.pos.x - opts->prev_cam.pos.x) < 1e-6
		&& fabs(opts->cur_cam.pos.y - opts->prev_cam.pos.y) < 1e-6
		&& fabs(opts->cur_cam.pos.z - opts->prev_cam.pos.z) < 1e-6
		&& fabs(opts->cur_cam.forward.x - opts->prev_cam.forward.x) < 1e-6)
	{
		taa_get_jitter(opts->taa_frame - 1, &jc.x, &jc.y);
		taa_get_jitter(opts->taa_frame - 2, &jp.x, &jp.y);
		o->x = fmax(0.0, fmin(gui->win.size.x - 1, d.x + round(jc.x - jp.x)));
		o->y = fmax(0.0, fmin(gui->win.size.y - 1, d.y + round(jc.y - jp.y)));
	}
	hist = opts->prev_color[o->y * opts->prev_render_size.x + o->x];
	clamp_hist(gui, d, &hist);
	c[0] = rt_unpack_color_v(((uint32_t *)gui->win.addr)[d.y
			* gui->win.size.x + d.x]);
	c[1] = rt_unpack_color_v(hist);
	c[0].x = (a * c[0].x + (256 - a) * c[1].x) >> 8;
	c[0].y = (a * c[0].y + (256 - a) * c[1].y) >> 8;
	c[0].z = (a * c[0].z + (256 - a) * c[1].z) >> 8;
	opts->taa_buf[d.y * gui->win.size.x + d.x] = rt_pack_color_v(c[0]);
}

void	taa_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_vec2i	d;
	t_vec2i	o;

	d.y = y_start;
	while (d.y < (int)y_end)
	{
		d.x = 0;
		while (d.x < (int)gui->win.size.x)
		{
			if (gui->opts.prev_valid && reproject_taa(gui, d.x, d.y, &o))
				taa_p(gui, &gui->opts, d, &o);
			else
				gui->opts.taa_buf[d.y * gui->win.size.x + d.x]
					= ((uint32_t *)gui->win.addr)[d.y * gui->win.size.x + d.x];
			d.x++;
		}
		d.y++;
	}
}

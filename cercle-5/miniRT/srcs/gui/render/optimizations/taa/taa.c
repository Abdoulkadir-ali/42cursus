/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:03:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Halton low-discrepancy sequence for sub-pixel jitter.
** base 2 for x, base 3 for y — standard TAA choice.
*/
static double	halton(size_t i, size_t base)
{
	double	f;
	double	r;

	f = 1.0;
	r = 0.0;
	while (i > 0)
	{
		f /= (double)base;
		r += f * (double)(i % base);
		i /= base;
	}
	return (r);
}

/*
** Returns the jitter for frame index n in [-0.5, 0.5] NDC sub-pixel space.
*/
void	taa_get_jitter(size_t frame, double *jx, double *jy)
{
	size_t	idx;

	idx = (frame % TAA_SEQ_LEN) + 1;
	*jx = halton(idx, 2) - 0.5;
	*jy = halton(idx, 3) - 0.5;
}

/*
** Reprojects pixel (dx, dy) from current into previous frame screen space.
** Returns false if reprojection is invalid (behind camera, out of bounds,
** or depth discontinuity indicating disocclusion).
*/
static bool	reproject_taa(t_gui *gui, size_t dx, size_t dy,
	size_t *ox, size_t *oy)
{
	t_optimizations	*o;
	t_vec3			wp;
	t_vec3			rel;
	t_vec3			ray_dir;
	double			ndc_x;
	double			ndc_y;
	double			cz;
	double			prev_d;
	size_t			pw;
	size_t			ph;

	o = &gui->opts;
	pw = (size_t)o->prev_render_size.x;
	ph = (size_t)o->prev_render_size.y;
	if (pw == 0 || ph == 0)
		return (false);
	ndc_x = (2.0 * (dx + 0.5) / (size_t)gui->win.size.x - 1.0) * o->cur_half_w;
	ndc_y = (1.0 - 2.0 * (dy + 0.5) / (size_t)gui->win.size.y) * o->cur_half_h;
	ray_dir = vec3_norm(vec3_add(o->cur_cam.forward,
				vec3_add(vec3_scale(o->cur_cam.right, ndc_x),
					vec3_scale(o->cur_cam.up, ndc_y))));
	wp = vec3_add(o->cur_cam.pos,
			vec3_scale(ray_dir, (double)o->depth_buf[dy * pw + dx]));
	rel = vec3_sub(wp, o->prev_cam.pos);
	cz = vec3_dot(rel, o->prev_cam.forward);
	if (cz < 1e-4)
		return (false);
	*ox = (size_t)((vec3_dot(rel, o->prev_cam.right) / cz / o->prev_half_w
				+ 1.0) * pw * 0.5);
	*oy = (size_t)((1.0 - vec3_dot(rel, o->prev_cam.up) / cz
				/ o->prev_half_h) * ph * 0.5);
	if (*ox >= pw || *oy >= ph)
		return (false);
	prev_d = (double)o->prev_depth[*oy * pw + *ox];
	if (prev_d > 1e-4 && o->depth_buf[dy * pw + dx] > 1e-4)
	{
		if (fabs(cz - prev_d) / fmaxf((float)cz, (float)prev_d)
			> TAA_DEPTH_THR)
			return (false);
	}
	return (true);
}

/*
** Blends one pixel: alpha * current + (1-alpha) * history.
** Channels extracted, blended in integer space.
*/
static uint32_t	blend_taa(uint32_t cur, uint32_t hist)
{
	size_t	cr;
	size_t	cg;
	size_t	cb;
	size_t	hr;
	size_t	hg;
	size_t	hb;
	size_t	a;
	size_t	b;

	a = (size_t)(TAA_ALPHA * 256.0f);
	b = 256 - a;
	cr = (cur >> 16) & 0xFF;
	cg = (cur >> 8) & 0xFF;
	cb = cur & 0xFF;
	hr = (hist >> 16) & 0xFF;
	hg = (hist >> 8) & 0xFF;
	hb = hist & 0xFF;
	return (((a * cr + b * hr) / 256) << 16
		| ((a * cg + b * hg) / 256) << 8
		| ((a * cb + b * hb) / 256));
}

/*
** Band worker: for each render pixel in [y_start, y_end),
** reproject into prev frame and accumulate into taa_buf.
*/
void	taa_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	size_t			rw;
	size_t			dx;
	size_t			dy;
	size_t			ox;
	size_t			oy;
	uint32_t		cur;

	o = &gui->opts;
	rw = (size_t)gui->win.size.x;
	dy = y_start;
	while (dy < y_end)
	{
		dx = 0;
		while (dx < rw)
		{
			cur = ((uint32_t *)gui->win.addr)[dy * rw + dx];
			if (o->prev_valid && reproject_taa(gui, dx, dy, &ox, &oy))
				o->taa_buf[dy * rw + dx] = blend_taa(cur,
						o->prev_color[oy * (size_t)o->prev_render_size.x + ox]);
			else
				o->taa_buf[dy * rw + dx] = cur;
			dx++;
		}
		dy++;
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

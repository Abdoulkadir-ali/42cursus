/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:04:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

static bool	depth_reject(t_optimizations *o, size_t nx, size_t ny, double cz)
{
	size_t	rx;
	size_t	ry;
	float	cur_d;

	rx = nx * (size_t)o->prev_render_size.x / (size_t)o->prev_render_size.x;
	ry = ny * (size_t)o->prev_render_size.y / (size_t)o->prev_render_size.y;
	cur_d = o->depth_buf[ry * (size_t)o->prev_render_size.x + rx];
	if (cur_d > 1e29f || (float)cz < 1e-4f)
		return (false);
	return (fabsf((float)cz - cur_d) / fmaxf((float)cz, cur_d) > DEPTH_THRESH);
}

static t_vec3	get_wp(t_optimizations *o, t_vec2 ndc, size_t idx)
{
	t_vec3	dir;

	dir = repro_get_dir(o->prev_cam, ndc);
	return (vec3_add(o->prev_cam.pos,
			vec3_scale(dir, (double)o->prev_depth[idx])));
}

static void	project_pixel(t_gui *gui, size_t idx, t_vec2i p)
{
	t_optimizations	*o;
	t_vec2			ndc;
	t_vec2i			n;
	t_reproj		r;
	double			cz;

	o = &gui->opts;
	ndc = repro_get_ndc(p, o->prev_render_size,
			vec2(o->prev_half_w, o->prev_half_h));
	r.cam = o->cur_cam;
	r.half = vec2(o->cur_half_w, o->cur_half_h);
	r.size = gui->win.disp_size;
	if (repro_world_to_screen(r, get_wp(o, ndc, idx), &n, &cz))
	{
		if (!depth_reject(o, (size_t)n.x, (size_t)n.y, cz))
		{
			o->reproj_buf[(size_t)n.y * gui->win.disp_size.x + (size_t)n.x]
				= o->prev_color[idx];
			o->reproj_tag[(size_t)n.y * gui->win.disp_size.x + (size_t)n.x]
				= o->reproj_gen;
		}
	}
}

void	scatter_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	size_t			rw;
	size_t			px;
	size_t			py;

	o = &gui->opts;
	rw = (size_t)o->prev_render_size.x;
	py = y_start;
	while (py < y_end)
	{
		px = 0;
		while (px < rw)
		{
			project_pixel(gui, py * rw + px, vec2i((int)px, (int)py));
			px++;
		}
		py++;
	}
}

void	scatter_frame(t_gui *gui)
{
	gui_parallel_task_worker(gui, TASK_SCATTER);
}

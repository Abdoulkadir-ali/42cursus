/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

static void	interp_pixel(t_gui *gui, t_vec2i p)
{
	t_optimizations	*o;
	t_vec2			ndc;
	t_vec3			wp;
	t_vec2i			n;
	t_reproj		r;

	o = &gui->opts;
	ndc = repro_get_ndc(p, o->prev_render_size,
			vec2(o->prev_half_w, o->prev_half_h));
	wp = vec3_add(o->prev_cam.pos, vec3_scale(repro_get_dir(o->prev_cam, ndc),
				(double)o->prev_depth[p.y
				* o->prev_render_size.x + p.x]));
	r.cam = o->interp_cam;
	r.half = o->interp_half;
	r.size = gui->win.disp_size;
	if (repro_world_to_screen(r, wp, &n, NULL))
		o->interp_buf[n.y * gui->win.disp_size.x + n.x]
			= o->prev_color[p.y * o->prev_render_size.x
			+ p.x];
}

void	interp_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	t_vec2i			p;

	o = &gui->opts;
	o->interp_cam = lerp_cam(o, (double)o->interp_alpha);
	o->interp_half.x = lerp_half(o->prev_half_w, o->cur_half_w,
			o->interp_alpha);
	o->interp_half.y = lerp_half(o->prev_half_h, o->cur_half_h,
			o->interp_alpha);
	p.y = y_start;
	while (p.y < y_end)
	{
		p.x = 0;
		while (p.x < o->prev_render_size.x)
		{
			interp_pixel(gui, p);
			p.x++;
		}
		p.y++;
	}
}

void	interp_frame(t_gui *gui, double alpha)
{
	t_optimizations	*o;
	size_t			dn;

	o = &gui->opts;
	if (!o->interp_buf || !o->prev_depth || !o->prev_color)
		return ;
	dn = gui->win.disp_size.x * gui->win.disp_size.y;
	ft_memset(o->interp_buf, 0, dn * sizeof(uint32_t));
	o->interp_alpha = (float)alpha;
	gui_parallel_task_worker(gui, TASK_INTERP);
}

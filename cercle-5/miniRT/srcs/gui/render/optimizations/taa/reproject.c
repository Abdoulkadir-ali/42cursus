/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reproject.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

static t_vec3	get_wp_taa(t_gui *gui, size_t dx, size_t dy)
{
	t_optimizations	*o;
	t_vec2			ndc;
	t_vec3			dir;
	size_t			pw;

	o = &gui->opts;
	pw = gui->win.size.x;
	ndc = repro_get_ndc(vec2i(dx, dy), gui->win.size,
			vec2(o->cur_half_w, o->cur_half_h));
	dir = repro_get_dir(o->cur_cam, ndc);
	return (vec3_add(o->cur_cam.pos,
			vec3_scale(dir, (double)o->depth_buf[dy * pw + dx])));
}

bool	reproject_taa(t_gui *gui, size_t dx, size_t dy, t_vec2i *out)
{
	t_optimizations	*o;
	double			cz;
	t_reproj		r;

	o = &gui->opts;
	r.cam = o->prev_cam;
	r.size = o->prev_render_size;
	if (r.size.x == 0 || r.size.y == 0)
		return (false);
	r.half = vec2(o->prev_half_w, o->prev_half_h);
	if (!repro_world_to_screen(r, get_wp_taa(gui, dx, dy), out, &cz))
		return (false);
	return (fabs(cz - o->prev_depth[out->y * r.size.x
				+ out->x]) / fmaxf((float)cz,
			(float)o->prev_depth[out->y * r.size.x
				+ out->x]) < TAA_DEPTH_THR);
}

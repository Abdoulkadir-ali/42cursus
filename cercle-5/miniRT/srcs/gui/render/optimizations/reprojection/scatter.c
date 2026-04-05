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

/*
** Returns true if the pixel at screen pos n[] has a depth discontinuity
** compared to cz (the reprojected depth), rejecting edge bleeding.
*/
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

/*
** Projects one pixel from prev frame into the current display buffer.
*/
static void	project_pixel(t_gui *gui, size_t idx, t_vec2i p)
{
	t_optimizations	*o;
	t_vec2			ndc;
	t_vec3			wp;
	t_vec3			rel;
	size_t			nx;
	size_t			ny;
	double			cz;

	o = &gui->opts;
	ndc.x = (2.0 * (p.x + 0.5) / o->prev_render_size.x - 1.0) * o->prev_half_w;
	ndc.y = (1.0 - 2.0 * (p.y + 0.5) / o->prev_render_size.y) * o->prev_half_h;
	wp = vec3_add(o->prev_cam.pos, vec3_scale(vec3_norm(vec3_add(o->prev_cam.forward,
					vec3_add(vec3_scale(o->prev_cam.right, ndc.x),
						vec3_scale(o->prev_cam.up, ndc.y)))),
				(double)o->prev_depth[idx]));
	rel = vec3_sub(wp, o->cur_cam.pos);
	cz = vec3_dot(rel, o->cur_cam.forward);
	if (cz < 1e-4)
		return ;
	nx = (size_t)((vec3_dot(rel, o->cur_cam.right) / cz / o->cur_half_w + 1.0)
			* gui->win.disp_size.x * 0.5);
	ny = (size_t)((1.0 - vec3_dot(rel, o->cur_cam.up) / cz / o->cur_half_h)
			* gui->win.disp_size.y * 0.5);
	if (nx < (size_t)gui->win.disp_size.x
		&& ny < (size_t)gui->win.disp_size.y
		&& !depth_reject(o, nx, ny, cz))
	{
		o->reproj_buf[ny * gui->win.disp_size.x + nx] = o->prev_color[idx];
		o->reproj_tag[ny * gui->win.disp_size.x + nx] = o->reproj_gen;
	}
}

/*
** Scatters all pixels of the previous render into reproj_buf.
*/
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

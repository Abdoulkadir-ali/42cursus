/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:05:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Builds an interpolated camera transform at fraction alpha (0=prev, 1=cur).
** Lerps position and direction vectors; renormalises forward/right/up.
*/
static t_transform	lerp_cam(t_optimizations *o, double alpha)
{
	t_transform	t;
	double		b;

	b = 1.0 - alpha;
	t.pos = vec3_add(vec3_scale(o->prev_cam.pos, b),
			vec3_scale(o->cur_cam.pos, alpha));
	t.forward = vec3_norm(vec3_add(vec3_scale(o->prev_cam.forward, b),
				vec3_scale(o->cur_cam.forward, alpha)));
	t.right = vec3_norm(vec3_add(vec3_scale(o->prev_cam.right, b),
				vec3_scale(o->cur_cam.right, alpha)));
	t.up = vec3_norm(vec3_add(vec3_scale(o->prev_cam.up, b),
				vec3_scale(o->cur_cam.up, alpha)));
	return (t);
}

static double	lerp_half(double a, double b, double t)
{
	return (a * (1.0 - t) + b * t);
}

/*
** Projects one prev-frame pixel into interp_buf using the interpolated cam.
*/
static void	interp_pixel(t_gui *gui, t_transform *cam,
	double hw, double hh, size_t idx, t_vec2i p)
{
	t_optimizations	*o;
	t_vec3			ray_dir;
	t_vec3			wp;
	t_vec3			rel;
	double			ndc_x;
	double			ndc_y;
	size_t			nx;
	size_t			ny;
	double			cz;

	o = &gui->opts;
	ndc_x = (2.0 * (p.x + 0.5) / o->prev_render_size.x - 1.0) * o->prev_half_w;
	ndc_y = (1.0 - 2.0 * (p.y + 0.5) / o->prev_render_size.y) * o->prev_half_h;
	ray_dir = vec3_norm(vec3_add(o->prev_cam.forward,
				vec3_add(vec3_scale(o->prev_cam.right, ndc_x),
					vec3_scale(o->prev_cam.up, ndc_y))));
	wp = vec3_add(o->prev_cam.pos,
			vec3_scale(ray_dir, (double)o->prev_depth[idx]));
	rel = vec3_sub(wp, cam->pos);
	cz = vec3_dot(rel, cam->forward);
	if (cz < 1e-4)
		return ;
	nx = (size_t)((vec3_dot(rel, cam->right) / cz / hw + 1.0)
			* gui->win.disp_size.x * 0.5);
	ny = (size_t)((1.0 - vec3_dot(rel, cam->up) / cz / hh)
			* gui->win.disp_size.y * 0.5);
	if (nx < (size_t)gui->win.disp_size.x
		&& ny < (size_t)gui->win.disp_size.y)
		o->interp_buf[ny * (size_t)gui->win.disp_size.x + nx]
			= o->prev_color[idx];
}

/*
** Band worker: scatter prev-frame pixels through the interpolated camera.
*/
void	interp_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	t_transform		cam;
	double			hw;
	double			hh;
	double			alpha;
	size_t			rw;
	size_t			px;
	size_t			py;

	o = &gui->opts;
	alpha = (double)o->interp_alpha;
	cam = lerp_cam(o, alpha);
	hw = lerp_half(o->prev_half_w, o->cur_half_w, alpha);
	hh = lerp_half(o->prev_half_h, o->cur_half_h, alpha);
	rw = (size_t)o->prev_render_size.x;
	py = y_start;
	while (py < y_end)
	{
		px = 0;
		while (px < rw)
		{
			interp_pixel(gui, &cam, hw, hh, py * rw + px,
				vec2i((int)px, (int)py));
			px++;
		}
		py++;
	}
}

/*
** Entry point: clears interp_buf, sets alpha, dispatches parallel warp.
** Result sits in opts.interp_buf — caller decides when to blit it.
*/
void	interp_frame(t_gui *gui, double alpha)
{
	t_optimizations	*o;
	size_t			dn;

	o = &gui->opts;
	if (!o->interp_buf || !o->prev_depth || !o->prev_color)
		return ;
	dn = (size_t)gui->win.disp_size.x * (size_t)gui->win.disp_size.y;
	ft_memset(o->interp_buf, 0, dn * sizeof(uint32_t));
	o->interp_alpha = (float)alpha;
	gui_parallel_task_worker(gui, TASK_INTERP);
}

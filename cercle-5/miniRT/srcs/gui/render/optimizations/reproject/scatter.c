/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 09:39:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	project_pixel(t_gui *gui, size_t idx, t_vec2i p, size_t gen)
{
	t_vec2		ndc;
	t_vec3		wp;
	t_vec3		rel;
	int			n[2];
	double		cz;

	ndc.x = (2.0 * (p.x + 0.5) / gui->render.prev_render_size.x - 1.0)
		* gui->render.prev_half_w;
	ndc.y = (1.0 - 2.0 * (p.y + 0.5) / gui->render.prev_render_size.y)
		* gui->render.prev_half_h;
	wp = vec3_add(gui->render.prev_cam.pos, vec3_scale(vec3_norm(vec3_add(
					gui->render.prev_cam.forward, vec3_add(vec3_scale(
						gui->render.prev_cam.right, ndc.x), vec3_scale(
						gui->render.prev_cam.up, ndc.y)))),
				(double)gui->render.prev_depth[idx]));
	rel = vec3_sub(wp, gui->render.cur_cam.pos);
	cz = vec3_dot(rel, gui->render.cur_cam.forward);
	if (cz < 1e-4)
		return ;
	n[0] = (int)((vec3_dot(rel, gui->render.cur_cam.right) / cz
				/ gui->render.cur_half_w + 1.0) * gui->win.disp_size.x * 0.5);
	n[1] = (int)((1.0 - vec3_dot(rel, gui->render.cur_cam.up) / cz
				/ gui->render.cur_half_h) * gui->win.disp_size.y * 0.5);
	if (n[0] >= 0 && (size_t)n[0] < gui->win.disp_size.x
		&& n[1] >= 0 && (size_t)n[1] < gui->win.disp_size.y)
	{
		gui->render.reproj_buf[n[1] * gui->win.disp_size.x + n[0]]
			= (uint32_t)gui->render.prev_buf[idx];
		gui->render.reproj_tag[n[1] * gui->win.disp_size.x + n[0]] = gen;
	}
}

void	scatter_band(t_gui *gui, size_t y_start, size_t y_end)
{
	size_t	px;
	size_t	py;
	size_t	rw;

	rw = (size_t)gui->render.prev_render_size.x;
	py = y_start;
	while (py < y_end)
	{
		px = 0;
		while (px < rw)
		{
			if (gui->render.prev_depth[py * rw + px] < 1e29f)
				project_pixel(gui, py * rw + px,
					(t_vec2i){px, py}, gui->render.reproj_gen);
			px++;
		}
		py++;
	}
}

void	scatter_threaded(t_gui *gui)
{
	gui_parallel_task_worker(gui, TASK_SCATTER);
}

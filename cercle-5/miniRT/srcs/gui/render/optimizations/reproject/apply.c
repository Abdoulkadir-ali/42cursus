/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define REPROJ_ALPHA	224		/* ~88% prev, 12% new  (out of 256) */
#define CAM_EPS			1e-5

bool	camera_moved(t_gui *gui)
{
	t_vec3	dp;
	t_vec3	df;
	double	eps2;

	eps2 = CAM_EPS * CAM_EPS;
	dp = vec3_sub(gui->render.cur_cam.pos, gui->render.prev_cam.pos);
	if (vec3_dot(dp, dp) > eps2)
		return (true);
	df = vec3_sub(gui->render.cur_cam.forward, gui->render.prev_cam.forward);
	if (vec3_dot(df, df) > eps2)
		return (true);
	return (false);
}

static int	blend_pixel(int nc, int oc, int a)
{
	int	ia;

	ia = 256 - a;
	return (((a * ((oc >> 16) & 0xFF) + ia * ((nc >> 16) & 0xFF)) >> 8) << 16
		| ((a * ((oc >> 8) & 0xFF) + ia * ((nc >> 8) & 0xFF)) >> 8) << 8
		| (a * (oc & 0xFF) + ia * (nc & 0xFF)) >> 8);
}

void	apply_reproj_band(t_gui *gui, size_t y_start, size_t y_end)
{
	uint32_t	*disp;
	uint32_t	*reproj;
	size_t		*tag;
	size_t		gen;
	size_t		w;
	size_t		i;
	size_t		n;

	disp = (uint32_t *)gui->win.disp_addr;
	reproj = gui->render.reproj_buf;
	tag = gui->render.reproj_tag;
	gen = gui->render.reproj_gen;
	w = (size_t)gui->win.disp_size.x;
	i = y_start * w;
	n = y_end * w;
	while (i < n)
	{
		if (tag[i] == gen)
			disp[i] = (uint32_t)blend_pixel((int)disp[i], (int)reproj[i],
					REPROJ_ALPHA);
		i++;
	}
}

void	apply_reproj(t_gui *gui)
{
	gui_parallel_task_worker(gui, TASK_APPLY);
}

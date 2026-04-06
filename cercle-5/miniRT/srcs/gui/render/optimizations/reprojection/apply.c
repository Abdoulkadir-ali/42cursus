/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Blends one pixel: 88% reprojected prev, 12% new.
*/
static uint32_t	blend_pixel(uint32_t nc, uint32_t oc)
{
	size_t	ia;
	size_t	r;
	size_t	g;
	size_t	b;

	ia = 256 - REPROJ_ALPHA;
	r = (REPROJ_ALPHA * ((oc >> 16) & 0xFF) + ia * ((nc >> 16) & 0xFF)) >> 8;
	g = (REPROJ_ALPHA * ((oc >> 8) & 0xFF) + ia * ((nc >> 8) & 0xFF)) >> 8;
	b = (REPROJ_ALPHA * (oc & 0xFF) + ia * (nc & 0xFF)) >> 8;
	return ((uint32_t)((r << 16) | (g << 8) | b));
}

void	apply_reproj_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_optimizations	*o;
	uint32_t		*disp;
	size_t			w;
	size_t			i;

	o = &gui->opts;
	disp = (uint32_t *)gui->win.disp_addrs[gui->render.back_idx];
	w = gui->win.disp_size.x;
	i = y_start * w;
	while (i < y_end * w)
	{
		if (o->reproj_tag[i] == o->reproj_gen)
			disp[i] = blend_pixel(disp[i], o->reproj_buf[i]);
		i++;
	}
}

void	apply_reproj(t_gui *gui)
{
	gui_parallel_task_worker(gui, TASK_APPLY);
}

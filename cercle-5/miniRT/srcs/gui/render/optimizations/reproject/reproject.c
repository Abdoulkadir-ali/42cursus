/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reproject.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 09:00:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* declared in apply.c + scatter.c within this folder */
bool	camera_moved(t_gui *gui);
void	apply_reproj(t_gui *gui);
void	scatter_threaded(t_gui *gui);

static void	save_frame(t_gui *gui)
{
	size_t	n;
	float	*tmp;

	n = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	ft_memcpy(gui->render.prev_buf, gui->win.addr, n * sizeof(uint32_t));
	tmp = gui->render.prev_depth;
	gui->render.prev_depth = gui->render.depth_buf;
	gui->render.depth_buf = tmp;
	gui->render.prev_render_size = gui->win.size;
	gui->render.prev_cam = gui->render.cur_cam;
	gui->render.prev_half_w = gui->render.cur_half_w;
	gui->render.prev_half_h = gui->render.cur_half_h;
	gui->render.prev_step = 1;
	gui->render.prev_valid = true;
}

void	reproject_frame(t_gui *gui)
{
	if (!gui->render.reproj_buf || !gui->render.prev_depth)
		return ;
	gui->render.reproj_gen++;
	if (gui->render.reproj_gen == 0)
		gui->render.reproj_gen = 1;
	if (gui->render.prev_valid && camera_moved(gui))
	{
		scatter_threaded(gui);
		apply_reproj(gui);
	}
	save_frame(gui);
}

void	reproject_free(t_gui *gui)
{
	free(gui->render.depth_buf);
	free(gui->render.prev_depth);
	free(gui->render.reproj_buf);
	free(gui->render.reproj_tag);
	gui->render.depth_buf = NULL;
	gui->render.prev_depth = NULL;
	gui->render.reproj_buf = NULL;
	gui->render.reproj_tag = NULL;
}

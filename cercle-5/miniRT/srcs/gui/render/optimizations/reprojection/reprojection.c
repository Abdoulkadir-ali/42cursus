/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprojection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:04:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Saves the current rendered frame into opts for next-frame reprojection.
** Called before any post-processing so prev_color always holds the raw render.
*/
void	save_frame(t_gui *gui)
{
	t_optimizations	*o;
	size_t			n;
	float			*tmp;

	o = &gui->opts;
	n = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	ft_memcpy(o->prev_color, gui->win.addr, n * sizeof(uint32_t));
	tmp = o->prev_depth;
	o->prev_depth = o->depth_buf;
	o->depth_buf = tmp;
	o->prev_render_size = gui->win.size;
	o->prev_cam = o->cur_cam;
	o->prev_half_w = o->cur_half_w;
	o->prev_half_h = o->cur_half_h;
	o->prev_valid = true;
}

/*
** Warps the previous frame into the display buffer using scatter + apply.
*/
void	reproject_frame(t_gui *gui)
{
	t_optimizations	*o;

	o = &gui->opts;
	if (!o->reproj_buf || !o->prev_depth)
		return ;
	o->reproj_gen++;
	if (o->reproj_gen == 0)
		o->reproj_gen = 1;
	if (o->prev_valid)
	{
		scatter_frame(gui);
		apply_reproj(gui);
	}
}

/*
** Frees all buffers owned by t_optimizations.
*/
void	opts_free(t_gui *gui)
{
	t_optimizations	*o;

	o = &gui->opts;
	free(o->depth_buf);
	free(o->prev_depth);
	free(o->prev_color);
	free(o->reproj_buf);
	free(o->reproj_tag);
	free(o->interp_buf);
	free(o->taa_buf);
	o->depth_buf = NULL;
	o->prev_depth = NULL;
	o->prev_color = NULL;
	o->reproj_buf = NULL;
	o->reproj_tag = NULL;
	o->interp_buf = NULL;
	o->taa_buf = NULL;
}

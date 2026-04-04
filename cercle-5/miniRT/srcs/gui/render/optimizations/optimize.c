/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:29:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** optimize_frames — central dispatcher for all post-render optimizations.
**
** Each optimization is gated solely by its runtime boolean in
** gui->render.opts (t_optimization_settings).  Flip any flag from
** anywhere at runtime — keybinding, settings panel, debug console.
**
** Pipeline order:
**   adaptive_scale  — adjusts render.scale to target FPS (no pixel write)
**   reprojection    — warps previous frame to new camera position
**   temporal_blend  — legacy blend with prev_buf (disabled by default)
**   frame_interp    — synthetic in-between frame   (combo B — planned)
**   taa             — temporal anti-aliasing        (combo D — planned)
*/

void	optimize_frames(t_gui *gui, double delta)
{
	if (gui->render.opts.adaptive_scale)
		adaptive_scale(gui);
	if (gui->render.opts.reprojection)
		reproject_frame(gui);
	if (gui->render.opts.temporal_blend)
		blend_temporal(gui, delta);
	if (gui->render.opts.frame_interp)
		(void)delta; /* frame_interp(gui, delta); — combo B, planned */
	if (gui->render.opts.taa)
		(void)delta; /* taa_frame(gui); — combo D, planned */
	(void)delta;
}

void	optimizations_init(t_gui *gui)
{
	gui->render.opts.adaptive_scale = true;
	gui->render.opts.reprojection = true;
	gui->render.opts.temporal_blend = false;
	gui->render.opts.frame_interp = false;
	gui->render.opts.taa = false;
}

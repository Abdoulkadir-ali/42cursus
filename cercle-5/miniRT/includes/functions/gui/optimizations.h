/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 22:55:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_OPTIMIZATIONS_H
# define GUI_OPTIMIZATIONS_H

# include "render.h"

/*
** Main dispatcher — called once per rendered frame.
** Each optimization is guarded by its compile-time OPT_* flag
** AND its runtime toggle in gui->render.opts.
*/
void	optimize_frames(t_gui *gui, double delta);
void	optimizations_init(t_gui *gui);

/* Adaptive resolution scaling */
void	adaptive_scale(t_gui *gui);

/* Camera reprojection */
void	reproject_frame(t_gui *gui);
void	reproject_free(t_gui *gui);
void	scatter_band(t_gui *gui, size_t y_start, size_t n);
void	apply_reproj_band(t_gui *gui, size_t y_start, size_t n);
void	upscale_band(t_gui *gui, size_t y_start, size_t y_end);

/* Temporal blend (legacy, disabled by default) */
void	blend_temporal(t_gui *gui, double dt);
void	blend_free(t_gui *gui);

/* Frame interpolation — placeholder for combo B */
/* void	frame_interp(t_gui *gui, double dt); */

/* Temporal anti-aliasing — placeholder for combo D */
/* void	taa_frame(t_gui *gui); */

#endif

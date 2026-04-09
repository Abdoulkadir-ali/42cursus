/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 10:08:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATIONS_H
# define OPTIMIZATIONS_H

# include "render.h"

# define TAA_ALPHA		0.1f
# define TAA_DEPTH_THR	0.15f
# define TAA_SEQ_LEN	8

# define SCALE_MIN			1
# define SCALE_MAX			2
# define SCALE_FPS_LOW		10.0
# define SCALE_FPS_HIGH		20.0
# define SCALE_COOLDOWN_MS	2000

# define DEPTH_THRESH	0.15f
# define REPROJ_ALPHA	224

# define BLEND_TARGET_DT	0.04
# define BLEND_ALPHA_MIN	0.15f


typedef struct s_reproj
{
	t_transform	cam;
	t_vec2		half;
	t_vec2s		size;
}	t_reproj;


/*
** Main dispatcher — called once per rendered frame.
** Each optimization is guarded by its compile-time OPT_* flag
** AND its runtime toggle in gui->render.opts.
*/
void	optimize_frames(t_gui *gui, double delta);
void	optimizations_init(t_gui *gui);

/* Adaptive resolution scaling */
void	adaptive_scale(t_gui *gui);

/* Depth-aware bilinear upscale */
void	upscale_band(t_gui *gui, size_t y_start, size_t y_end);
bool	reproject_taa(t_gui *gui, size_t dx, size_t dy, t_vec2i *out);

/* Reprojection */
void	save_frame(t_gui *gui);
void	reproject_frame(t_gui *gui);
void	scatter_band(t_gui *gui, size_t y_start, size_t y_end);
void	apply_reproj_band(t_gui *gui, size_t y_start, size_t y_end);
void	opts_free(t_gui *gui);


t_vec2			repro_get_ndc(t_vec2i p, t_vec2s size, t_vec2 half);
t_vec3		repro_get_dir(t_transform cam, t_vec2 ndc);
bool		repro_world_to_screen(t_reproj repro, t_vec3 wp, t_vec2i *out_n,
				double *out_cz);
/* Frame interpolation */
void	interp_frame(t_gui *gui, double alpha);
void	interp_band(t_gui *gui, size_t y_start, size_t y_end);

t_transform	lerp_cam(t_optimizations *o, double alpha);
double		lerp_half(double a, double b, double t);
/* Temporal Anti-Aliasing */
void	taa_apply(t_gui *gui);
void	taa_band(t_gui *gui, size_t y_start, size_t y_end);
void	taa_get_jitter(size_t frame, double *jx, double *jy);

/* Temporal blend */
void	blend_temporal(t_gui *gui, double dt);
void	scatter_frame(t_gui *gui);
void	apply_reproj(t_gui *gui);
#endif

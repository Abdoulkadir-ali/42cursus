/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 02:10:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Allocates all buffers owned by t_optimizations and sets default flags.
*/
static void	init_rt_defaults(t_gui *gui)
{
	gui->opts.adaptive_scale = true;
	gui->opts.reprojection = true;
	gui->opts.temporal_blend = false;
	gui->opts.frame_interp = false;
	gui->opts.taa = false;
	gui->rt_engine.settings.blinn_phong = true;
	gui->rt_engine.settings.brightness = 50.0;
	gui->rt_engine.settings.contrast = 50.0;
	gui->rt_engine.settings.saturation = 50.0;
	gui->rt_engine.settings.gamma = 50.0;
	gui->rt_engine.settings.bloom_enabled = false;
	gui->rt_engine.settings.bloom_threshold = 220.0;
	gui->rt_engine.settings.bloom_intensity = 1.0;
	gui->rt_engine.settings.bloom_radius = 3.0;
	gui->rt_engine.settings.dof_enabled = false;
	gui->rt_engine.settings.dof_aperture = 0.1;
	gui->rt_engine.settings.dof_focal_dist = 10.0;
	gui->rt_engine.settings.ao_enabled = true;
	gui->rt_engine.settings.ao_samples = 8;
	gui->rt_engine.settings.ao_radius = 0.8;
	gui->rt_engine.settings.ao_strength = 0.65;
	gui->rt_engine.settings.fresnel_enabled = true;
	gui->rt_engine.settings.gi_enabled = true;
	gui->rt_engine.settings.gi_strength = 0.4;
	gui->rt_engine.settings.aces_enabled = true;
	gui->rt_engine.settings.beer_enabled = true;
	gui->rt_engine.settings.beer_density = 0.02;
	gui->rt_engine.settings.chroma_enabled = false;
	gui->rt_engine.settings.chroma_dispersion = 0.012;
	gui->rt_engine.settings.preset = RT_PRESET_NATURAL;
}

void	optimizations_init(t_gui *gui)
{
	size_t	rn;
	size_t	dn;

	rn = gui->win.disp_size.x * gui->win.disp_size.y;
	dn = gui->win.disp_size.x * gui->win.disp_size.y;
	gui->opts.depth_buf = ft_calloc(rn, sizeof(float));
	gui->opts.prev_depth = ft_calloc(rn, sizeof(float));
	gui->opts.prev_color = ft_calloc(rn, sizeof(uint32_t));
	gui->opts.reproj_buf = ft_calloc(dn, sizeof(uint32_t));
	gui->opts.reproj_tag = ft_calloc(dn, sizeof(size_t));
	gui->opts.reproj_gen = 1;
	gui->opts.prev_valid = false;
	gui->opts.interp_buf = ft_calloc(dn, sizeof(uint32_t));
	gui->opts.interp_alpha = 0.5f;
	gui->opts.taa_buf = ft_calloc(rn, sizeof(uint32_t));
	gui->opts.taa_frame = 0;
	gui->opts.taa_jitter_x = 0.0;
	gui->opts.taa_jitter_y = 0.0;
	gui->opts.bloom_buf = ft_calloc(dn, sizeof(uint32_t));
	gui->opts.bloom_tmp = ft_calloc(dn, sizeof(uint32_t));
	init_rt_defaults(gui);
}

/*
** Central dispatcher — called once per rendered frame after upscale.
** Pipeline: reprojection → temporal_blend.
** adaptive_scale is called before rendering in raytrace_step.
*/
void	optimize_frames(t_gui *gui, double delta)
{
	(void)delta;
	if (gui->opts.reprojection)
		reproject_frame(gui);
	if (gui->opts.taa || gui->rt_engine.settings.gi_enabled)
		taa_apply(gui);
	if (gui->rt_engine.settings.bloom_enabled)
		bloom_frame(gui);
}

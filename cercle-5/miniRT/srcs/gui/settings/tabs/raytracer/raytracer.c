/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:38:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"
#include "optimizations.h"

static void	init_rt_sliders(t_gui *gui, t_islider *sl)
{
	const char	*lbl[9] = {"Bright", "Contrast", "Sat", "Gamma", "Bloom Th",
		"Bloom Int", "Bloom Rad", "Aperture", "Focal Dist"};
	double		*ptr[9];
	double		m[18];
	int			i;

	ptr[0] = &gui->rt_engine.settings.brightness;
	ptr[1] = &gui->rt_engine.settings.contrast;
	ptr[2] = &gui->rt_engine.settings.saturation;
	ptr[3] = &gui->rt_engine.settings.gamma;
	ptr[4] = &gui->rt_engine.settings.bloom_threshold;
	ptr[5] = &gui->rt_engine.settings.bloom_intensity;
	ptr[6] = &gui->rt_engine.settings.bloom_radius;
	ptr[7] = &gui->rt_engine.settings.dof_aperture;
	ptr[8] = &gui->rt_engine.settings.dof_focal_dist;
	ft_memcpy(m, (double [18]){0, 100, 0, 100, 0, 100, 1, 100, 0, 255, 0, 3,
		1, 12, 0, 1, 0.5, 100}, sizeof(m));
	i = -1;
	while (++i < 9)
		sl[i] = (t_islider){(char *)lbl[i], m[i * 2], m[i * 2 + 1], ptr[i],
			on_color_change};
}

static void	draw_rt_radios(t_gui *gui, t_vec2i o, int *y)
{
	t_iradio	r[7];
	int			i;

	r[0] = init_iradio("Adaptive", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("AutoRes", &gui->opts.auto_fullres, NULL);
	r[2] = init_iradio("Reproj", &gui->opts.reprojection, NULL);
	r[3] = init_iradio("TAA", &gui->opts.taa, NULL);
	r[4] = init_iradio("Bloom", &gui->rt_engine.settings.bloom_enabled, NULL);
	r[5] = init_iradio("Blinn", &gui->rt_engine.settings.blinn_phong, NULL);
	r[6] = init_iradio("DOF", &gui->rt_engine.settings.dof_enabled, NULL);
	i = -1;
	while (++i < 7)
	{
		*y += 24;
		draw_radio_row(gui, (t_panel){vec2i(o.x, *y),
			vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, r[i]);
	}
}

static bool	click_rt_sl(t_gui *gui, t_vec2i mouse, t_vec2i o, int y)
{
	t_islider	sl[9];
	int			i;

	init_rt_sliders(gui, sl);
	i = -1;
	while (++i < 9)
		if (try_settings_slider_click(gui, mouse,
				vec2i(o.x + 8, y + 24 + i * 36), sl[i]))
			return (true);
	return (click_preset(gui, mouse, o, y + 348));
}

bool	click_settings_raytracer_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_iradio	r[7];
	int			y;
	int			i;

	y = o.y + 36;
	r[0] = init_iradio("A", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("R", &gui->opts.auto_fullres, NULL);
	r[2] = init_iradio("P", &gui->opts.reprojection, NULL);
	r[3] = init_iradio("T", &gui->opts.taa, NULL);
	r[4] = init_iradio("B", &gui->rt_engine.settings.bloom_enabled, NULL);
	r[5] = init_iradio("L", &gui->rt_engine.settings.blinn_phong, NULL);
	r[6] = init_iradio("D", &gui->rt_engine.settings.dof_enabled, NULL);
	i = -1;
	while (++i < 7)
	{
		if (try_radio_click(gui, mouse, (t_panel){vec2i(o.x, y),
				vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, r[i]))
			return (true);
		y += 24;
	}
	return (click_rt_sl(gui, mouse, o, y));
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_islider	sl[9];
	int			y;
	int			i;

	y = o.y + 12;
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + 8, y,
		COL_HOVER, "RAYTRACER");
	draw_rt_radios(gui, o, &y);
	init_rt_sliders(gui, sl);
	i = -1;
	while (++i < 9)
		draw_settings_slider(gui, vec2i(o.x + 8, y + 24 + i * 36), sl[i]);
}

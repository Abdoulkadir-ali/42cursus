/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 00:24:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	draw_rt_radios(t_gui *gui, t_vec2i o, int *y)
{
	t_iradio	r[6];
	size_t		i;

	r[0] = init_iradio("Scale", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("Reproj", &gui->opts.reprojection, NULL);
	r[2] = init_iradio("TAA", &gui->opts.taa, NULL);
	r[3] = init_iradio("Bloom", &gui->rt_engine.settings.bloom_enabled, NULL);
	r[4] = init_iradio("Blinn", &gui->rt_engine.settings.blinn_phong, NULL);
	r[5] = init_iradio("DOF", &gui->rt_engine.settings.dof_enabled, NULL);
	i = 0;
	while (i < 6)
	{
		*y += 24;
		draw_radio_row(gui, (t_panel){vec2i(o.x, *y),
			vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, r[i++]);
	}
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_islider	sl[14];
	t_iradio	vr[6];
	int			y;
	size_t		i;

	y = o.y + 12;
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + 8, y, COL_HOVER, "OPTS");
	draw_rt_radios(gui, o, &y);
	sl[0] = (t_islider){"Bright", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Contrast", 0.0, 100.0,
		&gui->rt_engine.settings.contrast, on_color_change};
	sl[2] = (t_islider){"Sat", 0.0, 100.0,
		&gui->rt_engine.settings.saturation, on_color_change};
	sl[3] = (t_islider){"Gamma", 1.0, 100.0,
		&gui->rt_engine.settings.gamma, on_color_change};
	sl[4] = (t_islider){"Bloom Th", 0.0, 255.0,
		&gui->rt_engine.settings.bloom_threshold, on_color_change};
	sl[5] = (t_islider){"Bloom Int", 0.0, 3.0,
		&gui->rt_engine.settings.bloom_intensity, on_color_change};
	sl[6] = (t_islider){"Bloom Rad", 1.0, 12.0,
		&gui->rt_engine.settings.bloom_radius, on_color_change};
	sl[7] = (t_islider){"Aperture", 0.0, 1.0,
		&gui->rt_engine.settings.dof_aperture, on_color_change};
	sl[8] = (t_islider){"Focal Dist", 0.5, 100.0,
		&gui->rt_engine.settings.dof_focal_dist, on_color_change};
	sl[9] = (t_islider){"AO Radius", 0.1, 5.0,
		&gui->rt_engine.settings.ao_radius, on_color_change};
	sl[10] = (t_islider){"AO Str", 0.0, 1.0,
		&gui->rt_engine.settings.ao_strength, on_color_change};
	sl[11] = (t_islider){"GI Str", 0.0, 2.0,
		&gui->rt_engine.settings.gi_strength, on_color_change};
	sl[12] = (t_islider){"Beer Den", 0.0, 0.2,
		&gui->rt_engine.settings.beer_density, on_color_change};
	sl[13] = (t_islider){"Chroma", 0.0, 0.1,
		&gui->rt_engine.settings.chroma_dispersion, on_color_change};
	vr[0] = init_iradio("AO", &gui->rt_engine.settings.ao_enabled, NULL);
	vr[1] = init_iradio("Fresnel", &gui->rt_engine.settings.fresnel_enabled, NULL);
	vr[2] = init_iradio("GI", &gui->rt_engine.settings.gi_enabled, NULL);
	vr[3] = init_iradio("ACES", &gui->rt_engine.settings.aces_enabled, NULL);
	vr[4] = init_iradio("Beer", &gui->rt_engine.settings.beer_enabled, NULL);
	vr[5] = init_iradio("Chroma", &gui->rt_engine.settings.chroma_enabled, NULL);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 48), sl[0]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 84), sl[1]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 120), sl[2]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 156), sl[3]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 192), sl[4]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 228), sl[5]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 264), sl[6]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 300), sl[7]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 336), sl[8]);
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		o.x + 8, y + 372, COL_HOVER, "VISUAL");
	i = 0;
	while (i < 6)
	{
		draw_radio_row(gui, (t_panel){vec2i(o.x, y + 386 + (int)i * 24),
			vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, vr[i]);
		i++;
	}
	draw_settings_slider(gui, vec2i(o.x + 8, y + 538), sl[9]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 574), sl[10]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 610), sl[11]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 646), sl[12]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 682), sl[13]);
	draw_preset_row(gui, o, y + 726);
}

static bool	click_rt_radios(t_gui *gui, t_vec2i mouse, t_vec2i o, int *y)
{
	t_iradio	r[6];
	size_t		i;

	r[0] = init_iradio("Scale", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("Reproj", &gui->opts.reprojection, NULL);
	r[2] = init_iradio("TAA", &gui->opts.taa, NULL);
	r[3] = init_iradio("Bloom", &gui->rt_engine.settings.bloom_enabled, NULL);
	r[4] = init_iradio("Blinn", &gui->rt_engine.settings.blinn_phong, NULL);
	r[5] = init_iradio("DOF", &gui->rt_engine.settings.dof_enabled, NULL);
	i = 0;
	while (i < 6)
	{
		if (try_radio_click(gui, mouse, (t_panel){vec2i(o.x, *y),
				vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, r[i]))
			return (true);
		*y += 24;
		i++;
	}
	return (false);
}

bool	click_settings_raytracer_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_islider	sl[14];
	t_iradio	vr[6];
	int			y;
	size_t		i;

	y = o.y + 36;
	if (click_rt_radios(gui, mouse, o, &y))
		return (true);
	y += 24;
	sl[0] = (t_islider){"Bright", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Contrast", 0.0, 100.0,
		&gui->rt_engine.settings.contrast, on_color_change};
	sl[2] = (t_islider){"Sat", 0.0, 100.0,
		&gui->rt_engine.settings.saturation, on_color_change};
	sl[3] = (t_islider){"Gamma", 1.0, 100.0,
		&gui->rt_engine.settings.gamma, on_color_change};
	sl[4] = (t_islider){"Bloom Th", 0.0, 255.0,
		&gui->rt_engine.settings.bloom_threshold, on_color_change};
	sl[5] = (t_islider){"Bloom Int", 0.0, 3.0,
		&gui->rt_engine.settings.bloom_intensity, on_color_change};
	sl[6] = (t_islider){"Bloom Rad", 1.0, 12.0,
		&gui->rt_engine.settings.bloom_radius, on_color_change};
	sl[7] = (t_islider){"Aperture", 0.0, 1.0,
		&gui->rt_engine.settings.dof_aperture, on_color_change};
	sl[8] = (t_islider){"Focal Dist", 0.5, 100.0,
		&gui->rt_engine.settings.dof_focal_dist, on_color_change};
	sl[9] = (t_islider){"AO Radius", 0.1, 5.0,
		&gui->rt_engine.settings.ao_radius, on_color_change};
	sl[10] = (t_islider){"AO Str", 0.0, 1.0,
		&gui->rt_engine.settings.ao_strength, on_color_change};
	sl[11] = (t_islider){"GI Str", 0.0, 2.0,
		&gui->rt_engine.settings.gi_strength, on_color_change};
	sl[12] = (t_islider){"Beer Den", 0.0, 0.2,
		&gui->rt_engine.settings.beer_density, on_color_change};
	sl[13] = (t_islider){"Chroma", 0.0, 0.1,
		&gui->rt_engine.settings.chroma_dispersion, on_color_change};
	vr[0] = init_iradio("AO", &gui->rt_engine.settings.ao_enabled, NULL);
	vr[1] = init_iradio("Fresnel", &gui->rt_engine.settings.fresnel_enabled, NULL);
	vr[2] = init_iradio("GI", &gui->rt_engine.settings.gi_enabled, NULL);
	vr[3] = init_iradio("ACES", &gui->rt_engine.settings.aces_enabled, NULL);
	vr[4] = init_iradio("Beer", &gui->rt_engine.settings.beer_enabled, NULL);
	vr[5] = init_iradio("Chroma", &gui->rt_engine.settings.chroma_enabled, NULL);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y), sl[0]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 36), sl[1]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 72), sl[2]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 108), sl[3]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 144), sl[4]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 180), sl[5]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 216), sl[6]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 252), sl[7]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 288), sl[8]))
		return (true);
	i = 0;
	while (i < 6)
	{
		if (try_radio_click(gui, mouse,
				(t_panel){vec2i(o.x, y + 326 + (int)i * 24),
				vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, vr[i]))
			return (true);
		i++;
	}
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 482), sl[9]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 518), sl[10]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 554), sl[11]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 590), sl[12]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 626), sl[13]))
		return (true);
	return (click_preset(gui, mouse, o, y + 670));
}

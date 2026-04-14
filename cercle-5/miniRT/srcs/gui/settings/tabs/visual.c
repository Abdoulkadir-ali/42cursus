/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	build_vr(t_gui *gui, t_iradio *vr)
{
	vr[0] = init_iradio("AO", &gui->rt_engine.settings.ao_enabled, NULL);
	vr[1] = init_iradio("Fresnel",
			&gui->rt_engine.settings.fresnel_enabled, NULL);
	vr[2] = init_iradio("GI", &gui->rt_engine.settings.gi_enabled, NULL);
	vr[3] = init_iradio("ACES", &gui->rt_engine.settings.aces_enabled, NULL);
	vr[4] = init_iradio("Beer", &gui->rt_engine.settings.beer_enabled, NULL);
	vr[5] = init_iradio("Chroma",
			&gui->rt_engine.settings.chroma_enabled, NULL);
	vr[6] = init_iradio("Stoch Lights",
			&gui->rt_engine.settings.stochastic_lights, NULL);
}

static void	build_sl(t_gui *gui, t_islider *sl)
{
	sl[0] = (t_islider){"AO Radius", 0.1, 5.0,
		&gui->rt_engine.settings.ao_radius, on_color_change};
	sl[1] = (t_islider){"AO Str", 0.0, 1.0,
		&gui->rt_engine.settings.ao_strength, on_color_change};
	sl[2] = (t_islider){"GI Str", 0.0, 2.0,
		&gui->rt_engine.settings.gi_strength, on_color_change};
	sl[3] = (t_islider){"Beer Den", 0.0, 0.2,
		&gui->rt_engine.settings.beer_density, on_color_change};
	sl[4] = (t_islider){"Chroma", 0.0, 0.1,
		&gui->rt_engine.settings.chroma_dispersion, on_color_change};
}

void	draw_settings_visual_tab(t_gui *gui, t_vec2i o)
{
	t_iradio	vr[7];
	t_islider	sl[5];
	int			y;
	int			i;

	build_vr(gui, vr);
	build_sl(gui, sl);
	y = o.y + 12;
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + 8, y,
		COL_HOVER, "VISUAL");
	i = -1;
	while (++i < 7)
	{
		y += 24;
		draw_radio_row(gui, (t_panel){vec2i(o.x, y),
			vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, vr[i]);
	}
	y += 24;
	i = -1;
	while (++i < 5)
		draw_settings_slider(gui, vec2i(o.x + 8, y + 24 + i * 36), sl[i]);
}

bool	click_settings_visual_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_iradio	vr[7];
	t_islider	sl[5];
	int			y;
	int			i;

	build_vr(gui, vr);
	build_sl(gui, sl);
	y = o.y + 36;
	i = -1;
	while (++i < 7)
	{
		if (try_radio_click(gui, mouse, (t_panel){vec2i(o.x, y),
				vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, vr[i]))
			return (true);
		y += 24;
	}
	y += 24;
	i = -1;
	while (++i < 5)
		if (try_settings_slider_click(gui, mouse,
				vec2i(o.x + 8, y + 24 + i * 36), sl[i]))
			return (true);
	return (false);
}

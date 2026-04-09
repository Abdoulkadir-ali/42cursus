/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	draw_rt_radios(t_gui *gui, t_vec2i o, int *y)
{
	t_iradio	r[4];
	size_t		i;

	r[0] = init_iradio("Scale", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("Reproj", &gui->opts.reprojection, NULL);
	r[2] = init_iradio("TAA", &gui->opts.taa, NULL);
	r[3] = init_iradio("Blinn", &gui->rt_engine.settings.blinn_phong, NULL);
	i = 0;
	while (i < 4)
	{
		*y += 24;
		draw_radio_row(gui, (t_panel){vec2i(o.x, *y),
			vec2s(SETTINGS_W - 16, 0), 0, 0, ""}, r[i++]);
	}
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_islider	sl[4];
	int			y;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y, COL_HOVER, "OPTS");
	draw_rt_radios(gui, o, &y);
	sl[0] = (t_islider){"Bright", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Contrast", 0.0, 100.0,
		&gui->rt_engine.settings.contrast, on_color_change};
	sl[2] = (t_islider){"Sat", 0.0, 100.0,
		&gui->rt_engine.settings.saturation, on_color_change};
	sl[3] = (t_islider){"Gamma", 1.0, 100.0,
		&gui->rt_engine.settings.gamma, on_color_change};
	draw_settings_slider(gui, vec2i(o.x + 8, y + 48), sl[0]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 84), sl[1]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 120), sl[2]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 156), sl[3]);
	draw_preset_row(gui, o, y + 200);
}

static bool	click_rt_radios(t_gui *gui, t_vec2i mouse, t_vec2i o, int *y)
{
	t_iradio	r[4];
	size_t		i;

	r[0] = init_iradio("Scale", &gui->opts.adaptive_scale, NULL);
	r[1] = init_iradio("Reproj", &gui->opts.reprojection, NULL);
	r[2] = init_iradio("TAA", &gui->opts.taa, NULL);
	r[3] = init_iradio("Blinn", &gui->rt_engine.settings.blinn_phong, NULL);
	i = 0;
	while (i < 4)
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
	t_islider	sl[4];
	int			y;

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
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y), sl[0]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 36), sl[1]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 72), sl[2]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 108), sl[3]))
		return (true);
	return (click_preset(gui, mouse, o, y + 152));
}

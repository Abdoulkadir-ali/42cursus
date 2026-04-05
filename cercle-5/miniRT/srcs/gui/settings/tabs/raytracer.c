/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:38:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static const char	*s_preset_names[RT_PRESET_COUNT] = {
	"Custom", "Natural", "Vivid", "Cinematic"
};

static void	apply_preset(t_gui *gui, t_rt_preset p)
{
	t_raytracer_settings	*s;

	s = &gui->rt_engine.settings;
	if (p == RT_PRESET_NATURAL)
	{
		s->brightness = 50.0; s->contrast = 52.0;
		s->saturation = 50.0; s->gamma = 55.0;
	}
	else if (p == RT_PRESET_VIVID)
	{
		s->brightness = 55.0; s->contrast = 65.0;
		s->saturation = 70.0; s->gamma = 48.0;
	}
	else if (p == RT_PRESET_CINEMATIC)
	{
		s->brightness = 45.0; s->contrast = 60.0;
		s->saturation = 35.0; s->gamma = 54.0;
	}
	gui->render.dirty = true;
}

static void	on_color_change(t_gui *gui)
{
	gui->rt_engine.settings.preset = RT_PRESET_CUSTOM;
	gui->render.dirty = true;
}

static void	draw_preset_row(t_gui *gui, t_vec2i o, int y)
{
	const char		*name;
	char			buf[64];
	int				px;

	name = s_preset_names[gui->rt_engine.settings.preset];
	px = o.x + 8;
	mlx_string_put(gui->win.mlx, gui->win.win, px, y, COL_HOVER, "Preset");
	snprintf(buf, sizeof(buf), "< %s >", name);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + SETTINGS_W / 2 - 30, y, 0xCCCCDD, buf);
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_iradio	r[5];
	t_islider	sl[4];
	int			y;
	int			i;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, COL_HOVER, "OPTIMIZATIONS");
	y += 24;
	r[0] = (t_iradio){"Adaptive Scale",
		&gui->opts.adaptive_scale, NULL};
	r[1] = (t_iradio){"Reprojection",
		&gui->opts.reprojection, NULL};
	r[2] = (t_iradio){"Temporal Blend",
		&gui->opts.temporal_blend, NULL};
	r[3] = (t_iradio){"Frame Interp",
		&gui->opts.frame_interp, NULL};
	r[4] = (t_iradio){"TAA",
		&gui->opts.taa, NULL};
	i = 0;
	while (i < 5)
	{
		draw_radio_row(gui, vec2i(o.x, y), r[i], SETTINGS_W - 16);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
	y += 8;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, COL_HOVER, "COLOR");
	y += 24;
	r[3] = (t_iradio){"Blinn-Phong Specular",
		&gui->rt_engine.settings.blinn_phong, NULL};
	draw_radio_row(gui, vec2i(o.x, y), r[3], SETTINGS_W - 16);
	y += SETTINGS_ROW_H + 8;
	sl[0] = (t_islider){"Brightness", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Contrast",   0.0, 100.0,
		&gui->rt_engine.settings.contrast,   on_color_change};
	sl[2] = (t_islider){"Saturation", 0.0, 100.0,
		&gui->rt_engine.settings.saturation, on_color_change};
	sl[3] = (t_islider){"Gamma",      1.0, 100.0,
		&gui->rt_engine.settings.gamma,      on_color_change};
	i = 0;
	while (i < 4)
	{
		draw_slider_row(gui, vec2i(o.x + 8, y), sl[i]);
		y += 36;
		i++;
	}
	y += 8;
	draw_preset_row(gui, o, y);
}

bool	click_settings_raytracer_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_iradio	r[5];
	t_islider	sl[4];
	int			y;
	int			i;
	int			preset_y;
	int			pw;

	y = o.y + 12 + 24;
	r[0] = (t_iradio){"Adaptive Scale",
		&gui->opts.adaptive_scale, NULL};
	r[1] = (t_iradio){"Reprojection",
		&gui->opts.reprojection, NULL};
	r[2] = (t_iradio){"Temporal Blend",
		&gui->opts.temporal_blend, NULL};
	r[3] = (t_iradio){"Frame Interp",
		&gui->opts.frame_interp, NULL};
	r[4] = (t_iradio){"TAA",
		&gui->opts.taa, NULL};
	i = 0;
	while (i < 5)
	{
		if (try_radio_click(gui, mouse, vec2i(o.x, y), r[i], SETTINGS_W - 16))
			return (true);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
	y += 8 + 24;
	r[3] = (t_iradio){"Blinn-Phong Specular",
		&gui->rt_engine.settings.blinn_phong, NULL};
	if (try_radio_click(gui, mouse, vec2i(o.x, y), r[3], SETTINGS_W - 16))
		return (true);
	y += SETTINGS_ROW_H + 8;
	sl[0] = (t_islider){"Brightness", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Contrast",   0.0, 100.0,
		&gui->rt_engine.settings.contrast,   on_color_change};
	sl[2] = (t_islider){"Saturation", 0.0, 100.0,
		&gui->rt_engine.settings.saturation, on_color_change};
	sl[3] = (t_islider){"Gamma",      1.0, 100.0,
		&gui->rt_engine.settings.gamma,      on_color_change};
	i = 0;
	while (i < 4)
	{
		if (try_islider_click(gui, mouse, vec2i(o.x + 8, y), sl[i]))
			return (true);
		y += 36;
		i++;
	}
	/* preset prev/next: clicking left half = prev, right half = next */
	y += 8;
	preset_y = y;
	pw = SETTINGS_W - 16;
	if (mouse.y >= (size_t)(preset_y - 8) && mouse.y <= (size_t)(preset_y + 16)
		&& mouse.x >= (size_t)(o.x + 8) && mouse.x <= (size_t)(o.x + 8 + pw))
	{
		t_rt_preset	cur;
		cur = gui->rt_engine.settings.preset;
		if (mouse.x < o.x + 8 + pw / 2)
			cur = (cur == 0) ? RT_PRESET_COUNT - 1 : cur - 1;
		else
			cur = (cur + 1) % RT_PRESET_COUNT;
		gui->rt_engine.settings.preset = cur;
		if (cur != RT_PRESET_CUSTOM)
			apply_preset(gui, cur);
		else
			gui->render.dirty = true;
		return (true);
	}
	return (false);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:18:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static const char	*g_preset_names[RT_PRESET_COUNT] = {
	"Custom", "Natural", "Vivid", "Cinematic"
};

static void	draw_preset_row(t_gui *gui, t_vec2i o, int y)
{
	const char		*name;
	char			buf[64];

	name = g_preset_names[gui->rt_engine.settings.preset];
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y, COL_HOVER, "Preset");
	snprintf(buf, sizeof(buf), "< %s >", name);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + SETTINGS_W / 2 - 30, y, 0xCCCCDD, buf);
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_iradio	r[4];
	t_islider	sl[2];
	int			y;
	size_t		i;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y, COL_HOVER, "OPTS");
	r[0] = (t_iradio){"Scale", &gui->opts.adaptive_scale, NULL};
	r[1] = (t_iradio){"Reproj", &gui->opts.reprojection, NULL};
	r[2] = (t_iradio){"TAA", &gui->opts.taa, NULL};
	r[3] = (t_iradio){"Blinn", &gui->rt_engine.settings.blinn_phong, NULL};
	i = -1;
	while (++i < 4)
	{
		y += 24;
		draw_radio_row(gui, (t_panel){vec2i(o.x, y), vec2i(SETTINGS_W - 16, 0),
			0, 0, ""}, r[i]);
	}
	sl[0] = (t_islider){"Bright", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Gamma", 1.0, 100.0,
		&gui->rt_engine.settings.gamma, on_color_change};
	draw_settings_slider(gui, vec2i(o.x + 8, y + 48), sl[0]);
	draw_settings_slider(gui, vec2i(o.x + 8, y + 84), sl[1]);
	draw_preset_row(gui, o, y + 128);
}

static bool	click_preset(t_gui *gui, t_vec2i mouse, t_vec2i o, int y)
{
	t_rt_preset	cur;

	cur = gui->rt_engine.settings.preset;
	if (mouse.y >= (size_t)y && mouse.y <= (size_t)y + 32)
	{
		if (mouse.x < o.x + 8 + (SETTINGS_W - 16) / 2)
		{
			if (cur == 0)
				cur = RT_PRESET_COUNT - 1;
			else
				cur--;
		}
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

static bool	click_rt_radios(t_gui *gui, t_vec2i mouse, t_vec2i o, int *y)
{
	t_iradio	r[4];
	size_t		i;

	r[0] = (t_iradio){"Scale", &gui->opts.adaptive_scale, NULL};
	r[1] = (t_iradio){"Reproj", &gui->opts.reprojection, NULL};
	r[2] = (t_iradio){"TAA", &gui->opts.taa, NULL};
	r[3] = (t_iradio){"Blinn", &gui->rt_engine.settings.blinn_phong, NULL};
	i = -1;
	while (++i < 4)
	{
		if (try_radio_click(gui, mouse, (t_panel){vec2i(o.x, *y),
				vec2i(SETTINGS_W - 16, 0), 0, 0, ""}, r[i]))
			return (true);
		*y += 24;
	}
	return (false);
}

bool	click_settings_raytracer_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_islider	sl[2];
	int			y;

	y = o.y + 36;
	if (click_rt_radios(gui, mouse, o, &y))
		return (true);
	y += 48;
	sl[0] = (t_islider){"Bright", 0.0, 100.0,
		&gui->rt_engine.settings.brightness, on_color_change};
	sl[1] = (t_islider){"Gamma", 1.0, 100.0,
		&gui->rt_engine.settings.gamma, on_color_change};
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y), sl[0]))
		return (true);
	if (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y + 36), sl[1]))
		return (true);
	return (click_preset(gui, mouse, o, y + 72));
}

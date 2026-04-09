/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static const char	*g_preset_names[RT_PRESET_COUNT] = {
	"Custom", "Natural", "Vivid", "Cinematic"
};

void	apply_preset(t_gui *gui, t_rt_preset p)
{
	t_raytracer_settings	*s;

	s = &gui->rt_engine.settings;
	if (p == RT_PRESET_NATURAL)
	{
		s->brightness = 50.0;
		s->contrast = 52.0;
		s->saturation = 50.0;
		s->gamma = 55.0;
	}
	else if (p == RT_PRESET_VIVID)
	{
		s->brightness = 55.0;
		s->contrast = 65.0;
		s->saturation = 70.0;
		s->gamma = 48.0;
	}
	else if (p == RT_PRESET_CINEMATIC)
	{
		s->brightness = 45.0;
		s->contrast = 60.0;
		s->saturation = 35.0;
		s->gamma = 54.0;
	}
	gui->render.dirty = true;
}

void	on_color_change(t_gui *gui)
{
	gui->rt_engine.settings.preset = RT_PRESET_CUSTOM;
	gui->render.dirty = true;
}

void	draw_preset_row(t_gui *gui, t_vec2i o, int y)
{
	const char		*name;
	char			buf[64];

	name = g_preset_names[gui->rt_engine.settings.preset];
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y + 14,
		COL_HOVER, "Preset");
	snprintf(buf, sizeof(buf), "< %s >", name);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + SETTINGS_W / 2 - 30, y + 14, 0xCCCCDD, buf);
}

bool	click_preset(t_gui *gui, t_vec2i mouse, t_vec2i o, int y)
{
	t_rt_preset	cur;

	cur = gui->rt_engine.settings.preset;
	if (mouse.y >= y && mouse.y <= y + 32)
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

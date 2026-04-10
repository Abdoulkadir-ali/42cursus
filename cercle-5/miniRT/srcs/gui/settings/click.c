/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 02:19:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static bool	click_tabs(t_gui *gui, t_vec2i mouse, t_vec2i o, int tab_w)
{
	int	i;

	if (mouse.y < o.y + SETTINGS_HDR_H
		|| mouse.y >= o.y + SETTINGS_HDR_H + SETTINGS_TABS_H)
		return (false);
	if (mouse.x < o.x || mouse.x >= o.x + SETTINGS_W)
		return (false);
	i = (mouse.x - o.x) / tab_w;
	if (i >= SETTINGS_TAB_COUNT)
		i = SETTINGS_TAB_COUNT - 1;
	gui->settings.tab = (t_settings_tab)i;
	gui->render.dirty = true;
	return (true);
}

static bool	click_top(t_gui *gui, t_vec2i mouse)
{
	int	bx;
	int	by;

	bx = gui->win.disp_size.x - 202;
	by = 30;
	if (mouse.x >= bx && mouse.x < bx + SETTINGS_BTN_W
		&& mouse.y >= by && mouse.y < by + SETTINGS_BTN_H)
	{
		if (gui->settings.visible)
			settings_close(gui);
		else
			settings_open(gui);
		return (true);
	}
	return (false);
}

static bool	click_content(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_vec2i	co;

	co = vec2i(o.x, o.y + SETTINGS_CONTENT_Y);
	if (gui->settings.tab == STAB_WINDOW)
		return (click_settings_window_tab(gui, mouse, co));
	if (gui->settings.tab == STAB_PHYSICS)
		return (click_settings_physics_tab(gui, mouse, co));
	if (gui->settings.tab == STAB_RAYTRACER)
		return (click_settings_raytracer_tab(gui, mouse, co));
	if (gui->settings.tab == STAB_VISUAL)
		return (click_settings_visual_tab(gui, mouse, co));
	return (false);
}

static bool	click_header(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	if (mouse.y >= o.y && mouse.y < o.y + SETTINGS_HDR_H)
	{
		if (mouse.x >= o.x + SETTINGS_W - 32)
		{
			settings_close(gui);
			return (true);
		}
		gui->settings.dragging = true;
		gui->settings.drag_offset = vec2i(
				mouse.x - o.x,
				mouse.y - o.y);
		return (true);
	}
	return (false);
}

bool	settings_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	o;

	if (click_top(gui, mouse))
		return (true);
	if (!gui->settings.visible)
		return (false);
	o = gui->settings.pos;
	if (mouse.x < o.x || mouse.x >= o.x + SETTINGS_W
		|| mouse.y < o.y || mouse.y >= o.y + SETTINGS_H)
	{
		settings_close(gui);
		return (true);
	}
	if (click_header(gui, mouse, o))
		return (true);
	if (click_tabs(gui, mouse, o, SETTINGS_W / SETTINGS_TAB_COUNT))
		return (true);
	return (click_content(gui, mouse, o));
}

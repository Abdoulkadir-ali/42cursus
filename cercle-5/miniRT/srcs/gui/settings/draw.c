/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:10:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static char	*g_tab_labels[SETTINGS_TAB_COUNT] = {
	"Raytracer", "Physics", "Window"
};

static void	draw_settings_btn(t_gui *gui)
{
	t_vec2i	p;
	int		bg;

	p.x = gui->win.disp_size.x - 202;
	p.y = 30;
	bg = 0x22222E;
	if (gui->settings.visible)
		bg = 0x2A3040;
	draw_panel(gui, (t_panel){p,
		vec2s(SETTINGS_BTN_W, SETTINGS_BTN_H), bg, COL_ACCENT, ""});
	mlx_string_put(gui->win.mlx, gui->win.win,
		p.x + 8, p.y + SETTINGS_BTN_H / 2 + 4, COL_TEXT, "Settings");
}

static void	draw_settings_tabs(t_gui *gui, t_vec2i o)
{
	int		tab_w;
	size_t	i;
	int		col;
	int		bg;

	tab_w = SETTINGS_W / SETTINGS_TAB_COUNT;
	i = 0;
	while (i < SETTINGS_TAB_COUNT)
	{
		bg = 0x16161F;
		col = COL_TEXT;
		if ((t_settings_tab)i == gui->settings.tab)
		{
			bg = 0x20202E;
			col = COL_ACCENT;
		}
		draw_panel(gui, (t_panel){
			vec2i(o.x + tab_w * i, o.y + SETTINGS_HDR_H),
			vec2s(tab_w, SETTINGS_TABS_H), bg, COL_BORDER, ""});
		mlx_string_put(gui->win.mlx, gui->win.win,
			o.x + tab_w * i + 8,
			o.y + SETTINGS_HDR_H + SETTINGS_TABS_H / 2 + 4,
			col, g_tab_labels[i++]);
	}
}

static void	dispatch_draw(t_gui *gui, t_vec2i o)
{
	t_vec2i	co;

	co = vec2i(o.x, o.y + SETTINGS_CONTENT_Y);
	if (gui->settings.tab == STAB_WINDOW)
		draw_settings_window_tab(gui, co);
	else if (gui->settings.tab == STAB_PHYSICS)
		draw_settings_physics_tab(gui, co);
	else if (gui->settings.tab == STAB_RAYTRACER)
		draw_settings_raytracer_tab(gui, co);
}

void	draw_settings(t_gui *gui)
{
	t_vec2i	o;
	int		y;

	draw_settings_btn(gui);
	if (!gui->settings.visible)
		return ;
	o = gui->settings.pos;
	draw_panel(gui, (t_panel){o, vec2s(SETTINGS_W, SETTINGS_H),
		COL_BG, COL_BORDER, ""});
	y = o.y + SETTINGS_HDR_H / 2 + 4;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 12, y, COL_ACCENT, "Settings");
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + SETTINGS_W - 24, y, 0xE04040, "X");
	draw_settings_tabs(gui, o);
	dispatch_draw(gui, o);
}

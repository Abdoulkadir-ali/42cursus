/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static const char	*g_tab_labels[SETTINGS_TAB_COUNT] = {
	"Raytracer", "Physics", "Window"
};

static void	draw_settings_btn(t_gui *gui)
{
	int	bx;
	int	by;
	int	bg;

	bx = (int)gui->win.disp_size.x - 202;
	by = 30;
	bg = 0x22222E;
	if (gui->settings.visible)
		bg = 0x2A3040;
	draw_panel(gui, (t_panel){vec2i(bx, by),
		vec2i(SETTINGS_BTN_W, SETTINGS_BTN_H), bg, COL_ACCENT, ""});
	mlx_string_put(gui->win.mlx, gui->win.win,
		bx + 8, by + SETTINGS_BTN_H / 2 + 4, COL_TEXT, "Settings");
}

static void	draw_settings_tabs(t_gui *gui, t_vec2i o)
{
	int	tab_w;
	int	i;
	int	col;
	int	bg;

	tab_w = SETTINGS_W / SETTINGS_TAB_COUNT;
	i = -1;
	while (++i < SETTINGS_TAB_COUNT)
	{
		bg = 0x16161F;
		col = COL_TEXT;
		if ((t_settings_tab)i == gui->settings.tab)
		{
			bg = 0x20202E;
			col = COL_ACCENT;
		}
		draw_panel(gui, (t_panel){
			vec2i((int)o.x + tab_w * i, (int)o.y + SETTINGS_HDR_H),
			vec2i(tab_w, SETTINGS_TABS_H), bg, COL_BORDER, ""});
		mlx_string_put(gui->win.mlx, gui->win.win,
			(int)o.x + tab_w * i + 8,
			(int)o.y + SETTINGS_HDR_H + SETTINGS_TABS_H / 2 + 4,
			col, (char *)g_tab_labels[i]);
	}
}

static void	dispatch_draw(t_gui *gui, t_vec2i o)
{
	t_vec2i	co;

	co = vec2i((int)o.x, (int)o.y + SETTINGS_CONTENT_Y);
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
	draw_panel(gui, (t_panel){o, vec2i(SETTINGS_W, SETTINGS_H),
		COL_BG, COL_BORDER, ""});
	y = (int)o.y + SETTINGS_HDR_H / 2 + 4;
	mlx_string_put(gui->win.mlx, gui->win.win,
		(int)o.x + 12, y, COL_ACCENT, "Settings");
	mlx_string_put(gui->win.mlx, gui->win.win,
		(int)o.x + SETTINGS_W - 24, y, 0xE04040, "X");
	draw_settings_tabs(gui, o);
	dispatch_draw(gui, o);
}

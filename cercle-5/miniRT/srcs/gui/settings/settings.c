/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:17:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static const char	*s_tab_labels[SETTINGS_TAB_COUNT] = {
	"Raytracer", "Physics", "Window"
};

void	settings_init(t_gui *gui)
{
	gui->settings.visible = false;
	gui->settings.tab = STAB_RAYTRACER;
	gui->settings.render_scale = (double)gui->render.scale;
	gui->settings.solver_iters
		= (double)gui->phys_engine.settings.solver_iterations;
	gui->settings.pos = vec2i(
			(int)gui->win.disp_size.x - SETTINGS_W - 16, 30);
	gui->settings.dragging = false;
}

void	settings_open(t_gui *gui)
{
	gui->settings.render_scale = (double)gui->render.scale;
	gui->settings.solver_iters
		= (double)gui->phys_engine.settings.solver_iterations;
	gui->settings.visible = true;
	gui->render.dirty = true;
}

void	settings_close(t_gui *gui)
{
	gui->settings.visible = false;
	gui->render.dirty = true;
}

static t_vec2i	settings_origin(t_gui *gui)
{
	return (gui->settings.pos);
}

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
			vec2i((int)o.x + tab_w * i, (int)o.y + SETTINGS_HDR_H),
			vec2i(tab_w, SETTINGS_TABS_H), bg, COL_BORDER, ""});
		mlx_string_put(gui->win.mlx, gui->win.win,
			(int)o.x + tab_w * i + 8,
			(int)o.y + SETTINGS_HDR_H + SETTINGS_TABS_H / 2 + 4,
			col, (char *)s_tab_labels[i]);
		i++;
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

	draw_settings_btn(gui);
	if (!gui->settings.visible)
		return ;
	o = settings_origin(gui);
	draw_panel(gui, (t_panel){o, vec2i(SETTINGS_W, SETTINGS_H),
		COL_BG, COL_BORDER, ""});
	mlx_string_put(gui->win.mlx, gui->win.win,
		(int)o.x + 12, (int)o.y + SETTINGS_HDR_H / 2 + 4, COL_ACCENT, "Settings");
	mlx_string_put(gui->win.mlx, gui->win.win,
		(int)o.x + SETTINGS_W - 24, (int)o.y + SETTINGS_HDR_H / 2 + 4,
		0xE04040, "X");
	draw_settings_tabs(gui, o);
	dispatch_draw(gui, o);
}

static bool	click_settings_btn(t_gui *gui, t_vec2i mouse)
{
	int	bx;
	int	by;

	bx = (int)gui->win.disp_size.x - 202;
	by = 30;
	if ((int)mouse.x >= bx && (int)mouse.x < bx + SETTINGS_BTN_W
		&& (int)mouse.y >= by && (int)mouse.y < by + SETTINGS_BTN_H)
	{
		if (gui->settings.visible)
			settings_close(gui);
		else
			settings_open(gui);
		return (true);
	}
	return (false);
}

static bool	click_close_btn(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	if ((int)mouse.x >= (int)o.x + SETTINGS_W - 32
		&& (int)mouse.x < (int)o.x + SETTINGS_W
		&& (int)mouse.y >= (int)o.y
		&& (int)mouse.y < (int)o.y + SETTINGS_HDR_H)
	{
		settings_close(gui);
		return (true);
	}
	return (false);
}

static bool	click_tab_bar(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	int	tab_w;
	int	i;

	if ((int)mouse.y < (int)o.y + SETTINGS_HDR_H
		|| (int)mouse.y >= (int)o.y + SETTINGS_HDR_H + SETTINGS_TABS_H)
		return (false);
	if ((int)mouse.x < (int)o.x || (int)mouse.x >= (int)o.x + SETTINGS_W)
		return (false);
	tab_w = SETTINGS_W / SETTINGS_TAB_COUNT;
	i = ((int)mouse.x - (int)o.x) / tab_w;
	if (i >= SETTINGS_TAB_COUNT)
		i = SETTINGS_TAB_COUNT - 1;
	gui->settings.tab = (t_settings_tab)i;
	gui->render.dirty = true;
	return (true);
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
	return (false);
}

bool	settings_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	o;

	if (click_settings_btn(gui, mouse))
		return (true);
	if (!gui->settings.visible)
		return (false);
	o = settings_origin(gui);
	if ((int)mouse.x < (int)o.x || (int)mouse.x >= (int)o.x + SETTINGS_W
		|| (int)mouse.y < (int)o.y || (int)mouse.y >= (int)o.y + SETTINGS_H)
	{
		settings_close(gui);
		return (true);
	}
	/* start drag if click is inside the title header */
	if ((int)mouse.y < (int)o.y + SETTINGS_HDR_H
		&& (int)mouse.x < (int)o.x + SETTINGS_W - 32)
	{
		gui->settings.dragging = true;
		gui->settings.drag_offset = vec2i(
				(int)mouse.x - (int)o.x,
				(int)mouse.y - (int)o.y);
		return (true);
	}
	if (click_close_btn(gui, mouse, o))
		return (true);
	if (click_tab_bar(gui, mouse, o))
		return (true);
	return (click_content(gui, mouse, o));
}

void	settings_handle_drag(t_gui *gui, t_vec2i mouse)
{
	int	nx;
	int	ny;
	int	max_x;
	int	max_y;

	if (!gui->settings.dragging)
		return ;
	nx = (int)mouse.x - (int)gui->settings.drag_offset.x;
	ny = (int)mouse.y - (int)gui->settings.drag_offset.y;
	max_x = (int)gui->win.disp_size.x - SETTINGS_W;
	max_y = (int)gui->win.disp_size.y - SETTINGS_H;
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	if (nx > max_x)
		nx = max_x;
	if (ny > max_y)
		ny = max_y;
	gui->settings.pos = vec2i(nx, ny);
	gui->render.dirty = true;
}

void	settings_end_drag(t_gui *gui)
{
	gui->settings.dragging = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 22:24:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	draw_crud_button(t_gui *gui, int x, int y,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){.x = x, .y = y, .w = CRUD_BTN_W, .h = CRUD_BTN_H,
		.bg = bg, .brd = COL_BORDER, .pos = vec2i(x, y),
		.size = vec2i(CRUD_BTN_W, CRUD_BTN_H)};
	draw_panel(gui, btn);
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 6, y + CRUD_BTN_H / 2, COL_TEXT, (char *)lbl);
}

static void	draw_crud_sep(t_gui *gui, int y)
{
	t_panel	sep;

	sep = (t_panel){.x = 0, .y = y, .w = SCENE_PANEL_W, .h = 2,
		.bg = COL_BORDER, .brd = COL_BORDER,
		.pos = vec2i(0, y), .size = vec2i(SCENE_PANEL_W, 2)};
	draw_panel(gui, sep);
}

void	draw_crud_buttons(t_gui *gui)
{
	int	y1;
	int	y2;
	int	del_bg;

	if (!gui->scene_panel.visible)
		return ;
	y1 = gui->win.disp_h - CRUD_PANEL_H + 4;
	y2 = y1 + CRUD_BTN_H + 4;
	del_bg = 0x22222E;
	if (gui->selection.active)
		del_bg = 0x38161A;
	draw_crud_sep(gui, gui->win.disp_h - CRUD_PANEL_H);
	draw_crud_button(gui, 2, y1, "+SP", 0x22222E);
	draw_crud_button(gui, 56, y1, "+PL", 0x22222E);
	draw_crud_button(gui, 110, y1, "+CY", 0x22222E);
	draw_crud_button(gui, 164, y1, "+CO", 0x22222E);
	draw_crud_button(gui, 2, y2, "+LT", 0x22222E);
	draw_crud_button(gui, 56, y2, "DEL", del_bg);
}

static bool	btn_hit(t_vec2i m, int x, int y)
{
	if (m.x < x || m.x >= x + CRUD_BTN_W)
		return (false);
	if (m.y < y || m.y >= y + CRUD_BTN_H)
		return (false);
	return (true);
}

static bool	crud_row1_click(t_gui *gui, t_vec2i mouse, int y1)
{
	if (btn_hit(mouse, 2, y1))
	{
		editor_add_sphere(gui);
		return (true);
	}
	if (btn_hit(mouse, 56, y1))
	{
		editor_add_plane(gui);
		return (true);
	}
	if (btn_hit(mouse, 110, y1))
	{
		editor_add_cylinder(gui);
		return (true);
	}
	if (btn_hit(mouse, 164, y1))
	{
		editor_add_cone(gui);
		return (true);
	}
	return (false);
}

static bool	crud_row2_click(t_gui *gui, t_vec2i mouse, int y2)
{
	if (btn_hit(mouse, 2, y2))
	{
		editor_add_light(gui);
		return (true);
	}
	if (btn_hit(mouse, 56, y2) && gui->selection.active)
	{
		editor_delete_selected(gui);
		return (true);
	}
	return (false);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	int		y1;
	int		y2;
	bool	hit;

	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	y1 = gui->win.disp_h - CRUD_PANEL_H + 4;
	y2 = y1 + CRUD_BTN_H + 4;
	hit = crud_row1_click(gui, mouse, y1);
	if (!hit)
		hit = crud_row2_click(gui, mouse, y2);
	return (hit);
}

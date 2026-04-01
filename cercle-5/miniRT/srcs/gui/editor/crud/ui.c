/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:55:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** Top toolbar: [+ Add]  [DEL]  — pinned to the top of the left panel.
** Clicking [+ Add] opens the popup modal (popup.c).
*/

static void	draw_crud_btn(t_gui *gui, int x, int y, int w, int h,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){.x = x, .y = y, .w = w, .h = h,
		.bg = bg, .brd = COL_BORDER, .pos = vec2i(x, y), .size = vec2i(w, h)};
	draw_panel(gui, btn);
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 6, y + h / 2, COL_TEXT, (char *)lbl);
}

void	draw_crud_buttons(t_gui *gui)
{
	int	del_bg;
	int	add_bg;

	if (!gui->scene_panel.visible)
		return ;
	add_bg = (gui->crud.popup != POPUP_NONE) ? 0x2A2A3A : 0x22222E;
	del_bg = gui->selection.active ? 0x38161A : 0x22222E;
	/* toolbar background */
	draw_crud_btn(gui, 0, 0, SCENE_PANEL_W, CRUD_PANEL_H, "", 0x12121C);
	/* separator line at bottom of toolbar */
	draw_crud_btn(gui, 0, CRUD_PANEL_H - 1, SCENE_PANEL_W, 1, "", COL_BORDER);
	/* [+ Add] */
	draw_crud_btn(gui, 4, 6, CRUD_ADD_W, CRUD_BTN_H, "+ Add", add_bg);
	/* [DEL] */
	draw_crud_btn(gui, CRUD_ADD_W + 10, 6,
		SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H, "DEL", del_bg);
}

static bool	btn_hit(t_vec2i m, int x, int y, int w, int h)
{
	return (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	if (mouse.x < 0 || mouse.x >= SCENE_PANEL_W)
		return (false);
	if (mouse.y < 0 || mouse.y >= CRUD_PANEL_H)
		return (false);
	if (btn_hit(mouse, 4, 6, CRUD_ADD_W, CRUD_BTN_H))
	{
		if (gui->crud.popup == POPUP_NONE)
			gui->crud.popup = POPUP_SHAPE;
		else
			gui->crud.popup = POPUP_NONE;
		gui->render.dirty = true;
		return (true);
	}
	if (btn_hit(mouse, CRUD_ADD_W + 10, 6,
			SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H)
		&& gui->selection.active)
	{
		editor_delete_selected(gui);
		gui->render.dirty = true;
		return (true);
	}
	return (true);
}


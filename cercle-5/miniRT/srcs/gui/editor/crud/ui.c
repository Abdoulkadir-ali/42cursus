/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** Top toolbar: [+ Add]  [DEL]  — pinned to the top of the left panel.
** Clicking [+ Add] opens the popup modal (popup.c).
*/

static void	draw_crud_btn(t_gui *gui, t_vec2i pos, t_vec2i size,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){
		.pos = pos, .size = size,
		.bg = bg, .brd = COL_BORDER};
	draw_panel(gui, btn);
	if (lbl && *lbl)
		mlx_string_put(gui->win.mlx, gui->win.win,
			pos.x + 6, pos.y + size.y / 2 + 4, COL_TEXT, (char *)lbl);
}

void	draw_crud_buttons(t_gui *gui)
{
	int	del_bg;
	int	add_bg;

	if (!gui->scene_panel.visible)
		return ;
	add_bg = 0x22222E;
	if (gui->crud.popup != POPUP_NONE)
		add_bg = 0x2A2A3A;
	del_bg = 0x22222E;
	if (gui->selection.active)
		del_bg = 0x38161A;
	/* toolbar background */
	draw_crud_btn(gui, vec2i(0, 0), vec2i(SCENE_PANEL_W, CRUD_PANEL_H),
		"", 0x12121C);
	/* separator line at bottom of toolbar */
	draw_crud_btn(gui, vec2i(0, CRUD_PANEL_H - 1), vec2i(SCENE_PANEL_W, 1),
		"", COL_BORDER);
	/* [+ Add] */
	draw_crud_btn(gui, vec2i(4, 6), vec2i(CRUD_ADD_W, CRUD_BTN_H),
		"+ Add", add_bg);
	/* [DEL] */
	draw_crud_btn(gui, vec2i(CRUD_ADD_W + 10, 6),
		vec2i(SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H), "DEL", del_bg);
}

static bool	btn_hit(t_vec2i m, t_vec2i pos, t_vec2i size)
{
	return (m.x >= pos.x && m.x < pos.x + size.x
		&& m.y >= pos.y && m.y < pos.y + size.y);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	if (mouse.x >= SCENE_PANEL_W)
		return (false);
	if (mouse.y >= CRUD_PANEL_H)
		return (false);
	if (btn_hit(mouse, vec2i(4, 6), vec2i(CRUD_ADD_W, CRUD_BTN_H)))
	{
		if (gui->crud.popup == POPUP_NONE)
			gui->crud.popup = POPUP_SHAPE;
		else
			gui->crud.popup = POPUP_NONE;
		gui->render.dirty = true;
		return (true);
	}
	if (btn_hit(mouse, vec2i(CRUD_ADD_W + 10, 6),
			vec2i(SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H))
		&& gui->selection.active)
	{
		editor_delete_selected(gui);
		gui->render.dirty = true;
		return (true);
	}
	return (true);
}

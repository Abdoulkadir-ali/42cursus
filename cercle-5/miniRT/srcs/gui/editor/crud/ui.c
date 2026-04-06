/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_crud_bar(t_gui *gui, size_t w, size_t h, size_t add_w)
{
	t_vec2s	d;
	int		bcol_add;
	int		bcol_del;
	int		by;

	d = gui->win.disp_size;
	by = d.y - ui_sy(CRUD_BTN_H + 26, d);
	bcol_add = COL_CRUD_BTN_BG;
	if (gui->crud.popup != POPUP_NONE)
		bcol_add = COL_CRUD_BTN_POPUP;
	bcol_del = COL_CRUD_BTN_BG;
	if (gui->selection.active)
		bcol_del = COL_CRUD_BTN_DEL;
	draw_crud_btn(gui, (t_panel){vec2i(0, by - ui_sy(6, d)),
		vec2s(w, h + ui_sy(12, d)), COL_CRUD_BG, COL_CRUD_BG, ""});
	draw_crud_btn(gui, (t_panel){vec2i(0, by - ui_sy(7, d)),
		vec2s(w, 1), COL_BORDER, COL_BORDER, ""});
	draw_crud_btn(gui, (t_panel){vec2i(ui_sx(4, d), by),
		vec2s(add_w, h), bcol_add, COL_ACCENT, "+ Add"});
	draw_crud_btn(gui, (t_panel){vec2i(add_w + ui_sx(10, d), by),
		vec2s(w - add_w - ui_sx(16, d), h), bcol_del, COL_ACCENT, "DEL"});
}

void	draw_crud_buttons(t_gui *gui)
{
	t_vec2s	d;
	size_t	w;
	size_t	h;
	size_t	add_w;

	if (!gui->scene_panel.visible)
		return ;
	draw_scene_header(gui);
	d = gui->win.disp_size;
	w = gui->scene_panel.width;
	h = ui_sy(CRUD_BTN_H, d);
	add_w = ui_sx(CRUD_ADD_W, d);
	draw_crud_bar(gui, w, h, add_w);
}

static void	handle_add_btn(t_gui *gui)
{
	if (gui->crud.popup == POPUP_NONE)
		gui->crud.popup = POPUP_SHAPE;
	else
		gui->crud.popup = POPUP_NONE;
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	size_t	w;
	size_t	h;
	size_t	add_w;
	int		by;

	d = gui->win.disp_size;
	w = gui->scene_panel.width;
	h = ui_sy(CRUD_BTN_H, d);
	add_w = ui_sx(CRUD_ADD_W, d);
	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	if ((size_t)mouse.x >= w)
		return (false);
	by = d.y - ui_sy(CRUD_BTN_H + 26, d);
	if (mouse.y < (by - ui_sy(7, d)))
		return (false);
	if (phit(mouse, vec2i(ui_sx(4, d), by), vec2s(add_w, h)))
		handle_add_btn(gui);
	else if (phit(mouse, vec2i(add_w + ui_sx(10, d), by),
			vec2s(w - add_w - ui_sx(16, d), h)) && gui->selection.active)
		editor_delete_selected(gui);
	else
		return (true);
	return (true);
}

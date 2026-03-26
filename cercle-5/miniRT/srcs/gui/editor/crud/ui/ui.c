/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/*
** Top toolbar: [+ Add]  [DEL]  — pinned to the top of the left panel.
** Clicking [+ Add] opens the popup modal (popup.c).
*/
static bool	btn_hit(t_vec2i m, t_btn_rect r)
{
	if (m.x < r.x || m.x >= r.x + r.w)
		return (false);
	if (m.y < r.y || m.y >= r.y + r.h)
		return (false);
	return (true);
}

static bool	handle_add_click(t_gui *gui, t_vec2i mouse, t_btn_rect add_rect)
{
	if (!btn_hit(mouse, add_rect))
		return (false);
	if (gui->crud->popup == POPUP_NONE)
		gui->crud->popup = POPUP_SHAPE;
	else
		gui->crud->popup = POPUP_NONE;
	gui->render.dirty = true;
	return (true);
}

static bool	handle_del_click(t_gui *gui, t_vec2i mouse, t_btn_rect del_rect)
{
	if (!btn_hit(mouse, del_rect))
		return (false);
	if (!gui->selection->active)
		return (false);
	editor_delete_selected(gui);
	gui->render.dirty = true;
	return (true);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_btn_rect	add_rect;
	t_btn_rect	del_rect;

	if (!gui->scene || !gui->scene_panel->visible)
		return (false);
	if (mouse.x < 0 || mouse.x >= SCENE_PANEL_W)
		return (false);
	if (mouse.y < 0 || mouse.y >= CRUD_PANEL_H)
		return (false);
	add_rect.x = 4;
	add_rect.y = 6;
	add_rect.w = CRUD_ADD_W;
	add_rect.h = CRUD_BTN_H;
	if (handle_add_click(gui, mouse, add_rect))
		return (true);
	del_rect.x = CRUD_ADD_W + 10;
	del_rect.y = 6;
	del_rect.w = SCENE_PANEL_W - CRUD_ADD_W - 16;
	del_rect.h = CRUD_BTN_H;
	if (handle_del_click(gui, mouse, del_rect))
		return (true);
	return (true);
}

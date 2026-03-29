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
static bool	handle_add_click(t_gui *gui, t_vec2i mouse, t_gui_box add_rect)
{
	if (!phit(mouse, add_rect))
		return (false);
	if (gui->crud->popup == POPUP_NONE)
		gui->crud->popup = POPUP_SHAPE;
	else
		gui->crud->popup = POPUP_NONE;
	gui->render.dirty = true;
	return (true);
}

static bool	handle_del_click(t_gui *gui, t_vec2i mouse, t_gui_box del_rect)
{
	if (!phit(mouse, del_rect))
		return (false);
	if (!gui->selection->active)
		return (false);
	editor_delete_selected(gui);
	gui->render.dirty = true;
	return (true);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_gui_box	add_rect;
	t_gui_box	del_rect;

	if (!gui->scene || !gui->scene_panel->visible)
		return (false);
	if (mouse.x < 0 || mouse.x >= SCENE_PANEL_W)
		return (false);
	if (mouse.y < 0 || mouse.y >= CRUD_PANEL_H)
		return (false);
	add_rect.pos = vec2i(4, 6);
	add_rect.size = vec2i(CRUD_ADD_W, CRUD_BTN_H);
	if (handle_add_click(gui, mouse, add_rect))
		return (true);
	del_rect.pos = vec2i(CRUD_ADD_W + 10, 6);
	del_rect.size = vec2i(SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H);
	if (handle_del_click(gui, mouse, del_rect))
		return (true);
	return (true);
}

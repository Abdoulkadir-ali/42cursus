/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_crud_btn(t_gui *gui, t_panel btn, const char *lbl)
{
	draw_panel(gui, btn);
	gui_draw_string(gui, (char *)lbl, btn.box.pos.x + 6, btn.box.pos.y + btn.box.size.y / 2, COL_TEXT);
}

static void	draw_crud_buttons_bg(t_gui *gui)
{
	t_panel	panel;

	ft_memset(&panel, 0, sizeof(t_panel));
	panel.bg = 0x12121C;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(0, 0);
	panel.box.size = vec2i(SCENE_PANEL_W, CRUD_PANEL_H);
	draw_crud_btn(gui, panel, "");
	panel.bg = COL_BORDER;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(0, CRUD_PANEL_H - 1);
	panel.box.size = vec2i(SCENE_PANEL_W, 1);
	draw_crud_btn(gui, panel, "");
}

static void	draw_crud_buttons_actions(t_gui *gui, int add_bg, int del_bg)
{
	t_panel	panel;

	ft_memset(&panel, 0, sizeof(t_panel));
	panel.bg = add_bg;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(4, 6);
	panel.box.size = vec2i(CRUD_ADD_W, CRUD_BTN_H);
	draw_crud_btn(gui, panel, "+ Add");
	panel.bg = del_bg;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(CRUD_ADD_W + 10, 6);
	panel.box.size = vec2i(SCENE_PANEL_W - CRUD_ADD_W - 16, CRUD_BTN_H);
	draw_crud_btn(gui, panel, "DEL");
}

void	draw_crud_buttons(t_gui *gui)
{
	int	add_bg;
	int	del_bg;

	if (!gui->scene_panel->visible)
		return ;
	if (gui->crud->popup != POPUP_NONE)
		add_bg = 0x2A2A3A;
	else
		add_bg = 0x22222E;
	if (gui->selection->active)
		del_bg = 0x38161A;
	else
		del_bg = 0x22222E;
	draw_crud_buttons_bg(gui);
	draw_crud_buttons_actions(gui, add_bg, del_bg);
}

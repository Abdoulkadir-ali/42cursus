/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_crud_btn(t_gui *gui, t_panel btn, const char *lbl, int col)
{
	int	tx;
	int	ty;

	draw_panel(gui, btn);
	tx = btn.box.pos.x + (btn.box.size.x - ft_strlen(lbl) * 6) / 2;
	ty = btn.box.pos.y + btn.box.size.y / 2;
	gui_draw_string(gui, (char *)lbl, tx, ty, col);
}

static void	draw_crud_buttons_bg(t_gui *gui)
{
	t_panel	panel;

	ft_memset(&panel, 0, sizeof(t_panel));
	panel.bg = COL_HEADER;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(0, 0);
	panel.box.size = vec2i(SCENE_PANEL_W, CRUD_PANEL_H);
	draw_panel(gui, panel);
}

static void	draw_crud_buttons_actions(t_gui *gui, int add_bg, int del_bg)
{
	t_panel	panel;
	int		gap;

	ft_memset(&panel, 0, sizeof(t_panel));
	gap = 8;
	panel.bg = add_bg;
	panel.brd = COL_BORDER;
	panel.box.pos = vec2i(gap, (CRUD_PANEL_H - CRUD_BTN_H) / 2);
	panel.box.size = vec2i(CRUD_ADD_W, CRUD_BTN_H);
	draw_crud_btn(gui, panel, "Add", COL_TEXT);
	panel.bg = del_bg;
	panel.box.pos = vec2i(CRUD_ADD_W + gap * 2, (CRUD_PANEL_H - CRUD_BTN_H) / 2);
	panel.box.size = vec2i(CRUD_ADD_W, CRUD_BTN_H);
	draw_crud_btn(gui, panel, "Delete", gui->selection->active ? COL_ERROR : COL_TEXT_DIM);
}

void	draw_crud_buttons(t_gui *gui)
{
	int	add_bg;
	int	del_bg;

	if (!gui->scene_panel->visible)
		return ;
	if (gui->crud->popup != POPUP_NONE)
		add_bg = COL_ACCENT_DIM;
	else
		add_bg = COL_BG_CARD;
	if (gui->selection->active)
		del_bg = 0x7F1D1D;
	else
		del_bg = COL_BG_CARD;
	draw_crud_buttons_bg(gui);
	draw_crud_buttons_actions(gui, add_bg, del_bg);
}

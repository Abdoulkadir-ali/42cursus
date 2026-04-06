/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:07:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_path_field(t_gui *gui, t_vec2i o, size_t modal_h)
{
	t_vec2s	d;
	char	display[64];
	t_panel	field;

	d = gui->win.disp_size;
	field.pos = vec2i(o.x + ui_sx(POPUP_PAD, d),
			o.y + ui_sy(36 + POPUP_PAD + 24, d));
	field.size = ui_size(POPUP_W - POPUP_PAD * 2, POPUP_ITEM_H, d);
	field.bg = COL_MODAL_BG;
	field.brd = COL_BORDER;
	if (gui->crud.path_error)
		field.brd = COL_ERROR;
	draw_panel(gui, field);
	if (gui->crud.path_len <= 40)
		snprintf(display, sizeof(display), "> %s_", gui->crud.path_buf);
	else
		snprintf(display, sizeof(display), "> ...%s_",
			gui->crud.path_buf + gui->crud.path_len - 37);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD + 6, d),
		field.pos.y + field.size.y / 2 + ui_sy(4, d),
		gui->crud.path_error ? COL_RED_SOFT : COL_TEXT, display);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD, d),
			o.y + modal_h - ui_sy(36, d)), ui_size(80, 26, d),
		COL_CRUD_BTN_BG, COL_BORDER, "<- Back"});
}

void	draw_popup_mesh_path(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
		o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Add Mesh \xe2\x80\x94 Path");
	draw_path_field(gui, o, modal_h);
	draw_popup_btn(gui, (t_panel){
		vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d), o.y + modal_h - ui_sy(36, d)),
		ui_size(70, 26, d), COL_CRUD_BTN_BG, COL_ACCENT, "Load"});
	draw_popup_btn(gui, (t_panel){
		vec2i(o.x + ui_sx(POPUP_W - 90 - POPUP_PAD, d),
			o.y + modal_h - ui_sy(36, d)),
		ui_size(86, 26, d), 0x2A1A1A, COL_BORDER, "Cancel"});
}

void	draw_popup_tex_path(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	modal_h;
	t_panel	field;
	char	display[64];
	int		field_y;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 24 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
		o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Texture \xe2\x80\x94 Path");
	field_y = o.y + ui_sy(36 + POPUP_PAD + 24, d);
	field.pos = vec2i(o.x + ui_sx(POPUP_PAD, d), field_y);
	field.size = ui_size(POPUP_W - POPUP_PAD * 2, POPUP_ITEM_H, d);
	field.bg = COL_MODAL_BG;
	field.brd = gui->crud.path_error ? COL_ERROR : COL_BORDER;
	field.lbl = NULL;
	draw_panel(gui, field);
	if (gui->crud.path_len <= 40)
		snprintf(display, sizeof(display), "> %s_", gui->crud.path_buf);
	else
		snprintf(display, sizeof(display), "> ...%s_",
			gui->crud.path_buf + gui->crud.path_len - 37);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + ui_sx(POPUP_PAD + 6, d),
		field_y + (int)field.size.y / 2 + ui_sy(4, d),
		gui->crud.path_error ? COL_RED_SOFT : COL_TEXT, display);
	if (gui->crud.path_error)
		mlx_string_put(gui->win.mlx, gui->win.win,
			o.x + ui_sx(POPUP_PAD, d),
			field_y + (int)field.size.y + ui_sy(6, d),
			COL_ERROR, "File not found / load failed");
	draw_popup_btn(gui, (t_panel){
		vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d),
			o.y + modal_h - ui_sy(36, d)),
		ui_size(70, 26, d), COL_CRUD_BTN_BG, COL_ACCENT, "Load"});
	draw_popup_btn(gui, (t_panel){
		vec2i(o.x + ui_sx(POPUP_W - 90 - POPUP_PAD, d),
			o.y + modal_h - ui_sy(36, d)),
		ui_size(86, 26, d), 0x2A1A1A, COL_BORDER, "Cancel"});
}

void	draw_popup_mesh_fmt(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	bw;
	size_t	m_h;

	d = gui->win.disp_size;
	m_h = ui_sy(POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, m_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
		o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Add Mesh");
	bw = ui_sx((POPUP_W - POPUP_PAD * 3) / 2, d);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD, d),
				o.y + ui_sy(36 + POPUP_PAD, d)),
			ui_size(bw, POPUP_ITEM_H, d), COL_CRUD_BTN_BG, COL_BORDER, "OBJ"});
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + bw,
				o.y + ui_sy(36 + POPUP_PAD, d)),
			ui_size(bw, POPUP_ITEM_H, d), COL_CRUD_BTN_BG, COL_BORDER, "GLB"});
}

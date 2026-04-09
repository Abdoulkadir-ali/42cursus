/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_path_col(t_gui *gui, t_vec2i o, char *display, t_panel f)
{
	int		col;
	t_vec2s	d;

	d = gui->win.disp_size;
	col = COL_TEXT;
	if (gui->crud.path_error)
		col = COL_RED_SOFT;
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD + 6, d),
		f.pos.y + f.size.y / 2 + ui_sy(4, d), col, display);
}

void	draw_path_field(t_gui *gui, t_vec2i o, size_t modal_h)
{
	t_vec2s	d;
	char	display[2048];
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
	draw_path_col(gui, o, display, field);
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
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
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

static void	draw_tex_path_input(t_gui *gui, t_vec2i o, t_vec2s d, int f_y)
{
	t_panel	f;
	char	display[2048];
	int		col;

	f.pos = vec2i(o.x + ui_sx(POPUP_PAD, d), f_y);
	f.size = ui_size(POPUP_W - POPUP_PAD * 2, POPUP_ITEM_H, d);
	f.bg = COL_MODAL_BG;
	f.brd = COL_BORDER;
	if (gui->crud.path_error)
		f.brd = COL_ERROR;
	f.lbl = NULL;
	draw_panel(gui, f);
	if (gui->crud.path_len <= 40)
		snprintf(display, sizeof(display), "> %s_", gui->crud.path_buf);
	else
		snprintf(display, sizeof(display), "> ...%s_",
			gui->crud.path_buf + gui->crud.path_len - 37);
	col = COL_TEXT;
	if (gui->crud.path_error)
		col = COL_RED_SOFT;
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD + 6, d),
		f_y + (int)f.size.y / 2 + ui_sy(4, d), col, display);
}

void	draw_popup_tex_path(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 24 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
		o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Texture \xe2\x80\x94 Path");
	draw_tex_path_input(gui, o, d, o.y + ui_sy(36 + POPUP_PAD + 24, d));
	if (gui->crud.path_error)
		mlx_string_put_c(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d),
			o.y + ui_sy(36 + POPUP_PAD + 24 + POPUP_ITEM_H + 6, d),
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

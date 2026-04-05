/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_path_field(t_gui *gui, t_vec2i o, int modal_h)
{
	t_vec2i	d;
	char	display[64];
	t_panel	field;
	int		color;

	d = gui->win.disp_size;
	field.pos = vec2i(o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(36 + POPUP_PAD + 24, d));
	field.size = vec2i(ui_sx(POPUP_W - POPUP_PAD * 2, d), ui_sy(POPUP_ITEM_H, d));
	field.bg = 0x0D0D14;
	field.brd = COL_BORDER;
	if (gui->crud.path_error)
		field.brd = 0xFF4444;
	draw_panel(gui, field);
	if (gui->crud.path_len <= 40)
		snprintf(display, sizeof(display), "> %s_", gui->crud.path_buf);
	else
		snprintf(display, sizeof(display), "> ...%s_",
			gui->crud.path_buf + gui->crud.path_len - 37);
	color = COL_TEXT;
	if (gui->crud.path_error)
		color = 0xFF6666;
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD + 6, d),
		o.y + ui_sy(36 + POPUP_PAD + 24 + (POPUP_ITEM_H / 2) + 4, d), color, display);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD, d), o.y + modal_h - ui_sy(36, d)),
		vec2i(ui_sx(80, d), ui_sy(26, d)), 0x22222E, COL_BORDER, "\xe2\x86\x90 Back"});
}

void	draw_popup_mesh_path(t_gui *gui)
{
	t_vec2i	d;
	t_vec2i	o;
	int		modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(POPUP_PAD, d),
		COL_ACCENT, "Add Mesh \xe2\x80\x94 Path");
	draw_path_field(gui, o, modal_h);
}

void	draw_popup_mesh_fmt(t_gui *gui)
{
	t_vec2i	d;
	t_vec2i	o;
	int		bw;
	int		modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36, d);
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Add Mesh");
	bw = ui_sx((POPUP_W - POPUP_PAD * 3) / 2, d);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(36 + POPUP_PAD, d)),
		vec2i(bw, ui_sy(POPUP_ITEM_H, d)), 0x22222E, COL_BORDER, "OBJ"});
	draw_popup_btn(gui, (t_panel){vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + bw,
		o.y + ui_sy(36 + POPUP_PAD, d)), vec2i(bw, ui_sy(POPUP_ITEM_H, d)), 0x22222E,
		COL_BORDER, "GLB"});
}

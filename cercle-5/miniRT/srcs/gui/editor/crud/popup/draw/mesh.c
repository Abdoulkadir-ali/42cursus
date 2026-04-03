/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_path_field(t_gui *gui, t_vec2i o, int modal_h)
{
	char	display[64];
	t_panel	field;
	int		color;

	field.pos = vec2i(o.x + POPUP_PAD, o.y + 36 + POPUP_PAD + 24);
	field.size = vec2i(POPUP_W - POPUP_PAD * 2, POPUP_ITEM_H);
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
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + POPUP_PAD + 6,
		o.y + 36 + POPUP_PAD + 24 + (POPUP_ITEM_H / 2) + 4, color, display);
	draw_popup_btn(gui, (t_panel){vec2i(o.x + POPUP_PAD, o.y + modal_h - 36),
		vec2i(80, 26), 0x22222E, COL_BORDER, "\xe2\x86\x90 Back"});
}

void	draw_popup_mesh_path(t_gui *gui)
{
	t_vec2i	o;
	int		modal_h;

	modal_h = POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + POPUP_PAD, o.y + POPUP_PAD,
		COL_ACCENT, "Add Mesh \xe2\x80\x94 Path");
	draw_path_field(gui, o, modal_h);
}

void	draw_popup_mesh_fmt(t_gui *gui)
{
	t_vec2i	o;
	int		bw;
	int		modal_h;

	modal_h = POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + POPUP_PAD, o.y + POPUP_PAD, COL_ACCENT, "Add Mesh");
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	draw_popup_btn(gui, (t_panel){vec2i(o.x + POPUP_PAD, o.y + 36 \
+ POPUP_PAD), vec2i(bw, POPUP_ITEM_H), 0x22222E, COL_BORDER, "OBJ"});
	draw_popup_btn(gui, (t_panel){vec2i(o.x + POPUP_PAD * 2 + bw, \
o.y + 36 + POPUP_PAD), vec2i(bw, POPUP_ITEM_H), 0x22222E, \
COL_BORDER, "GLB"});
}

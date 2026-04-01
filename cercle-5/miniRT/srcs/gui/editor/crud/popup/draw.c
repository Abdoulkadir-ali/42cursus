/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 21:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_popup_mesh_path(t_gui *gui)
{
	char	display[64];
	t_vec2i	o;
	t_panel	field;
	int		modal_h;
	int		color;

	modal_h = POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + POPUP_PAD, o.y + POPUP_PAD,
		COL_ACCENT, "Add Mesh \xe2\x80\x94 Path");
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
		o.y + 36 + POPUP_PAD + 24 + POPUP_ITEM_H / 2 + 4, color, display);
	draw_popup_btn(gui, vec2i(o.x + POPUP_PAD, o.y + modal_h - 36),
		vec2i(80, 26), "\xe2\x86\x90 Back", 0x22222E);
}

static void	draw_popup_mesh_fmt(t_gui *gui)
{
	t_vec2i	o;
	int		bw;
	int		modal_h;

	modal_h = POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + POPUP_PAD, o.y + POPUP_PAD, COL_ACCENT, "Add Mesh");
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	draw_popup_btn(gui, vec2i(o.x + POPUP_PAD, o.y + 36 + POPUP_PAD),
		vec2i(bw, POPUP_ITEM_H), "OBJ", 0x22222E);
	draw_popup_btn(gui, vec2i(o.x + POPUP_PAD * 2 + bw, o.y + 36 + POPUP_PAD),
		vec2i(bw, POPUP_ITEM_H), "GLB", 0x22222E);
}

static void	draw_popup_shape(t_gui *gui)
{
	static const char	*lbl[11] = {"Sphere", "Plane", "Cyl", "Cone", "Light",
		"Tri", "Rect", "Pyramid", "Box", "Capsule", "Mesh"};
	t_vec2i				o;
	t_vec2i				s;
	int					i;

	draw_modal_bg(gui, POPUP_PAD * 2 + 36 + 4 * (POPUP_ITEM_H + 8) + 40, &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + POPUP_PAD, o.y + POPUP_PAD, COL_ACCENT, "Add Object");
	s = vec2i((POPUP_W - POPUP_PAD * 4) / 3, POPUP_ITEM_H);
	i = -1;
	while (++i < 11)
		draw_popup_btn(gui, vec2i(o.x + POPUP_PAD + (i % 3) * (s.x + POPUP_PAD),
				o.y + 36 + POPUP_PAD + (i / 3) * (s.y + 8)), s, lbl[i], 0x22222E);
}

void	draw_popup(t_gui *gui)
{
	if (gui->crud.popup == POPUP_SHAPE)
		draw_popup_shape(gui);
	else if (gui->crud.popup == POPUP_MESH_FMT)
		draw_popup_mesh_fmt(gui);
	else if (gui->crud.popup == POPUP_MESH_PATH)
		draw_popup_mesh_path(gui);
}

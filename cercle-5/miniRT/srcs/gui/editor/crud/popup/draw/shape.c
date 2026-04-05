/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_object_item(t_gui *gui, t_vec2i o, t_vec2i s, int i)
{
	static const char	*lbl[11] = {"Sphere", "Plane", "Cyl", "Cone", "Light",
		"Tri", "Rect", "Pyramid", "Box", "Capsule", "Mesh"};
	t_vec2i				d;
	t_vec2i				p;

	d = gui->win.disp_size;
	p.x = o.x + ui_sx(POPUP_PAD, d) + (i % 3) * (s.x + ui_sx(POPUP_PAD, d));
	p.y = o.y + ui_sy(36, d) + ui_sy(POPUP_PAD, d) + (i / 3) * (s.y + ui_sy(8, d));
	draw_popup_btn(gui, (t_panel){p, s, 0x22222E, COL_BORDER, lbl[i]});
}

void	draw_popup_shape(t_gui *gui)
{
	t_vec2i				d;
	t_vec2i				o;
	t_vec2i				s;
	int					i;

	d = gui->win.disp_size;
	draw_modal_bg(gui, ui_sy(POPUP_PAD * 2 + 36 + 4 * (POPUP_ITEM_H + 8) + 40, d), &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(POPUP_PAD, d), COL_ACCENT, "Add Object");
	s = vec2i(ui_sx((POPUP_W - POPUP_PAD * 4) / 3, d), ui_sy(POPUP_ITEM_H, d));
	i = 0;
	while (i < 11)
	{
		draw_object_item(gui, o, s, i);
		i++;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_object_item(t_gui *gui, t_vec2i o, t_vec2i s, int i)
{
	static const char	*lbl[11] = {"Sphere", "Plane", "Cyl", "Cone", "Light",
		"Tri", "Rect", "Pyramid", "Box", "Capsule", "Mesh"};
	t_vec2i				p;

	p.x = o.x + POPUP_PAD + (i % 3) * (s.x + POPUP_PAD);
	p.y = o.y + 36 + POPUP_PAD + (i / 3) * (s.y + 8);
	draw_popup_btn(gui, (t_panel){p, s, 0x22222E, COL_BORDER, lbl[i]});
}

static void	draw_popup_shape(t_gui *gui)
{
	t_vec2i				o;
	t_vec2i				s;
	int					i;

	draw_modal_bg(gui, POPUP_PAD * 2 + 36 + 4 * (POPUP_ITEM_H + 8) + 40, &o);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + POPUP_PAD, o.y + POPUP_PAD, COL_ACCENT, "Add Object");
	s = vec2i((POPUP_W - POPUP_PAD * 4) / 3, POPUP_ITEM_H);
	i = -1;
	while (++i < 11)
		draw_object_item(gui, o, s, i);
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

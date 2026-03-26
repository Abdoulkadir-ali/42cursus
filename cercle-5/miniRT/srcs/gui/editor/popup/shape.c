/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	dispatch_shape(t_gui *gui, int i)
{
	void	(*add[])(t_gui *) = { editor_add_sphere, editor_add_plane,
		editor_add_cylinder, editor_add_cone, editor_add_light, editor_add_tri,
		editor_add_rect, editor_add_pyramid, editor_add_box, editor_add_capsule};

	if (i >= 0 && i < 10)
		add[i](gui);
	gui->crud->popup = POPUP_NONE;
}

void	draw_popup_shape(t_gui *gui)
{
	static const char	*labs[11] = {"Sphere", "Plane", "Cylinder", "Cone",
		"Light", "Triangle", "Rectangle", "Pyramid", "Box", "Capsule", "Mesh \x21\x92"};
	int					bw;
	int					i;

	draw_modal_bg(gui);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->crud->pos.x + POPUP_PAD,
		gui->crud->pos.y + POPUP_PAD, COL_ACCENT, "Add Object");
	bw = (POPUP_W - POPUP_PAD * 4) / 3;
	i = 0;
	while (i < 11)
	{
		draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_PAD + (i % 3)
			* (bw + POPUP_PAD), gui->crud->pos.y + 36 + POPUP_PAD + (i / 3)
			* (POPUP_ITEM_H + 8)), vec2i(bw, POPUP_ITEM_H), labs[i],
			(i == 10) ? 0x1E2A1E : COL_POPUP_BTN);
		i++;
	}
	draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_W - 90 - POPUP_PAD,
		gui->crud->pos.y + 36 + POPUP_PAD + 4 * (POPUP_ITEM_H + 8) + 4),
		vec2i(90, 26), "Cancel", COL_POPUP_BTN_CANCEL);
}

bool	click_popup_shape(t_gui *gui, t_vec2i mouse)
{
	int	bw;
	int	i;

	bw = (POPUP_W - POPUP_PAD * 4) / 3;
	i = -1;
	while (++i < 11)
	{
		if (phit(mouse, vec2i(gui->crud->pos.x + POPUP_PAD + (i % 3)
			* (bw + POPUP_PAD), gui->crud->pos.y + 36 + POPUP_PAD + (i / 3)
			* (POPUP_ITEM_H + 8)), vec2i(bw, POPUP_ITEM_H)))
		{
			if (i == 10)
				gui->crud->popup = POPUP_MESH_FMT;
			else
				dispatch_shape(gui, i);
			return (true);
		}
	}
	if (phit(mouse, vec2i(gui->crud->pos.x + POPUP_W - 90 - POPUP_PAD,
		gui->crud->pos.y + 36 + POPUP_PAD + 4 * (POPUP_ITEM_H + 8) + 4),
		vec2i(90, 26)))
		gui->crud->popup = POPUP_NONE;
	return (true);
}


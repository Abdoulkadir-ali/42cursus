/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:07:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"

static void	dispatch_shape(t_gui *gui, t_type type)
{
	if (type == TYPE_SPHERE)
		editor_add_sphere(gui);
	else if (type == TYPE_PLANE)
		editor_add_plane(gui);
	else if (type == TYPE_CYLINDER)
		editor_add_cylinder(gui);
	else if (type == TYPE_CONE)
		editor_add_cone(gui);
	else if (type == TYPE_LIGHT)
		editor_add_light(gui);
	else if (type == TYPE_TRI)
		editor_add_tri(gui);
	else if (type == TYPE_RECT)
		editor_add_rect(gui);
	else if (type == TYPE_PYRAMID)
		editor_add_pyramid(gui);
	else if (type == TYPE_BOX)
		editor_add_box(gui);
	else if (type == TYPE_CAPSULE)
		editor_add_capsule(gui);
	gui->crud.popup = POPUP_NONE;
}

static t_type	idx_to_type(int i)
{
	static const t_type	map[11] = {
		TYPE_SPHERE, TYPE_PLANE, TYPE_CYLINDER, TYPE_CONE, TYPE_LIGHT,
		TYPE_TRI, TYPE_RECT, TYPE_PYRAMID, TYPE_BOX, TYPE_CAPSULE,
		TYPE_MESH
	};

	if (i < 0 || i > 10)
		return (TYPE_NONE);
	return (map[i]);
}

static bool	click_item(t_gui *gui, t_vec2i mouse, t_vec2i o, t_vec2s s)
{
	t_vec2s	d;
	t_vec2i	p;
	t_type	type;
	size_t	i;

	d = gui->win.disp_size;
	i = 0;
	while (i < 11)
	{
		p.x = o.x + ui_sx(POPUP_PAD, d) + (i % 3) * (s.x + ui_sx(POPUP_PAD, d));
		p.y = o.y + ui_sy(36 + POPUP_PAD, d) + (i / 3) * (s.y + ui_sy(8, d));
		if (phit(mouse, p, s))
		{
			type = idx_to_type(i);
			if (type == TYPE_MESH)
				gui->crud.popup = POPUP_MESH_FMT;
			else
				dispatch_shape(gui, type);
			gui->render.dirty = true;
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	click_popup_shape(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	t_vec2s	s;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 4 * (POPUP_ITEM_H + 8) + 40, d);
	o.x = (d.x - ui_sx(POPUP_W, d)) / 2;
	o.y = (d.y - (int)modal_h) / 2;
	s = ui_size((POPUP_W - POPUP_PAD * 4) / 3, POPUP_ITEM_H, d);
	return (click_item(gui, mouse, o, s));
}

bool	popup_handle_click(t_gui *gui, t_vec2i mouse)
{
	if (gui->crud.popup == POPUP_NONE)
		return (false);
	if (gui->crud.popup == POPUP_SHAPE)
		return (click_popup_shape(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_FMT)
		return (click_popup_mesh_fmt(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_PATH)
		return (click_popup_mesh_path(gui, mouse));
	if (gui->crud.popup == POPUP_TEX_PATH)
		return (click_popup_tex_path(gui, mouse));
	return (true);
}

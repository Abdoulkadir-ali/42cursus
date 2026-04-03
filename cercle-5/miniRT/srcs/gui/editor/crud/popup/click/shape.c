/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:07:27 by abdoali          ###   ########.fr       */
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

static bool	click_item(t_gui *gui, t_vec2i mouse, t_vec2i o, t_vec2i s)
{
	int		i;
	t_type	type;
	t_vec2i	p;

	i = 0;
	while (i < 11)
	{
		p.x = o.x + POPUP_PAD + (i % 3) * (s.x + POPUP_PAD);
		p.y = o.y + 36 + POPUP_PAD + (i / 3) * (s.y + 8);
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
	t_vec2i	o;
	t_vec2i	s;
	int		modal_h;

	modal_h = POPUP_PAD * 2 + 36 + 4 * (POPUP_ITEM_H + 8) + 40;
	o = vec2i((gui->win.disp_size.x - POPUP_W) / 2,
			(gui->win.disp_size.y - modal_h) / 2);
	s = vec2i((POPUP_W - POPUP_PAD * 4) / 3, POPUP_ITEM_H);
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
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:07:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	bw;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36, d);
	o.x = (d.x - ui_sx(POPUP_W, d)) / 2;
	o.y = (d.y - modal_h) / 2;
	bw = ui_sx((POPUP_W - POPUP_PAD * 3) / 2, d);
	if (phit(mouse, vec2i(o.x + ui_sx(POPUP_PAD, d),
				o.y + ui_sy(36 + POPUP_PAD, d)),
			ui_size(bw, POPUP_ITEM_H, d)))
	{
		gui->crud.mesh_fmt = MESH_FMT_OBJ;
		gui->crud.popup = POPUP_MESH_PATH;
		gui->crud.path_buf[0] = '\0';
		gui->crud.path_len = 0;
		gui->crud.path_error = false;
		gui->render.dirty = true;
	}
	if (phit(mouse, vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + (int)bw,
				o.y + ui_sy(36 + POPUP_PAD, d)),
			ui_size(bw, POPUP_ITEM_H, d)))
	{
		gui->crud.mesh_fmt = MESH_FMT_GLB;
		gui->crud.popup = POPUP_MESH_PATH;
		gui->crud.path_buf[0] = '\0';
		gui->crud.path_len = 0;
		gui->crud.path_error = false;
		gui->render.dirty = true;
	}
	return (true);
}

bool	click_popup_mesh_path(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36, d);
	o.x = (d.x - ui_sx(POPUP_W, d)) / 2;
	o.y = (d.y - (int)modal_h) / 2;
	if (phit(mouse, vec2i(o.x + ui_sx(POPUP_PAD, d),
				o.y + modal_h - ui_sy(36, d)),
			ui_size(80, 26, d)))
	{
		gui->crud.popup = POPUP_MESH_FMT;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (phit(mouse, vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d),
				o.y + modal_h - ui_sy(36, d)),
			ui_size(70, 26, d)))
	{
		popup_load_mesh(gui);
		return (true);
	}
	gui->crud.popup = POPUP_NONE;
	gui->crud.path_error = false;
	gui->render.dirty = true;
	return (true);
}

bool	click_popup_tex_path(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	modal_h;

	d = gui->win.disp_size;
	modal_h = ui_sy(POPUP_PAD * 2 + 36 + 24 + POPUP_ITEM_H + 16 + 36, d);
	o.x = (d.x - ui_sx(POPUP_W, d)) / 2;
	o.y = (d.y - (int)modal_h) / 2;
	if (phit(mouse, vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d),
				o.y + modal_h - ui_sy(36, d)),
			ui_size(70, 26, d)))
	{
		popup_submit_tex(gui);
		return (true);
	}
	gui->crud.popup = POPUP_NONE;
	gui->crud.path_error = false;
	gui->render.dirty = true;
	return (true);
}

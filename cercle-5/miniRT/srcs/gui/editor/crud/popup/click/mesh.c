/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	set_path_popup(t_gui *gui, t_mesh_fmt fmt)
{
	gui->crud.mesh_fmt = fmt;
	gui->crud.popup = POPUP_MESH_PATH;
	gui->crud.path_buf[0] = '\0';
	gui->crud.path_len = 0;
	gui->crud.path_error = false;
	gui->render.dirty = true;
}

bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	t_vec2i	p;
	size_t	bw;

	d = gui->win.disp_size;
	o = vec2i((d.x - ui_sx(POPUP_W, d)) / 2, (d.y - (int)ui_sy(POPUP_PAD * 2
					+ 36 + POPUP_ITEM_H + 16 + 36, d)) / 2);
	bw = ui_sx((POPUP_W - POPUP_PAD * 3) / 2, d);
	p = vec2i(o.x + ui_sx(POPUP_PAD, d), o.y + ui_sy(36 + POPUP_PAD, d));
	if (phit(mouse, p, ui_size(bw, POPUP_ITEM_H, d)))
		set_path_popup(gui, MESH_FMT_OBJ);
	p = vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + (int)bw,
			o.y + ui_sy(36 + POPUP_PAD, d));
	if (phit(mouse, p, ui_size(bw, POPUP_ITEM_H, d)))
		set_path_popup(gui, MESH_FMT_GLB);
	return (true);
}

bool	click_popup_mesh_path(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	m_h;

	d = gui->win.disp_size;
	m_h = ui_sy(POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36, d);
	o = vec2i((d.x - ui_sx(POPUP_W, d)) / 2, (d.y - (int)m_h) / 2);
	if (phit(mouse, vec2i(o.x + ui_sx(POPUP_PAD, d), o.y + m_h - ui_sy(36, d)),
			ui_size(80, 26, d)))
	{
		gui->crud.popup = POPUP_MESH_FMT;
		return (gui->crud.path_error = false, gui->render.dirty = true, true);
	}
	if (phit(mouse, vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d),
				o.y + m_h - ui_sy(36, d)), ui_size(70, 26, d)))
		return (popup_load_mesh(gui), true);
	gui->crud.popup = POPUP_NONE;
	return (gui->crud.path_error = false, gui->render.dirty = true, true);
}

bool	click_popup_tex_path(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	t_vec2i	o;
	size_t	m_h;

	d = gui->win.disp_size;
	m_h = ui_sy(POPUP_PAD * 2 + 36 + 24 + POPUP_ITEM_H + 16 + 36, d);
	o = vec2i((d.x - ui_sx(POPUP_W, d)) / 2, (d.y - (int)m_h) / 2);
	if (phit(mouse, vec2i(o.x + ui_sx((POPUP_W - 70) / 2, d),
				o.y + m_h - ui_sy(36, d)), ui_size(70, 26, d)))
		return (popup_submit_tex(gui), true);
	gui->crud.popup = POPUP_NONE;
	return (gui->crud.path_error = false, gui->render.dirty = true, true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
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
		gui->crud.popup = POPUP_MESH_PATH;
	if (phit(mouse, vec2i(o.x + ui_sx(POPUP_PAD * 2, d) + (int)bw,
				o.y + ui_sy(36 + POPUP_PAD, d)),
			ui_size(bw, POPUP_ITEM_H, d)))
		gui->crud.popup = POPUP_MESH_PATH;
	return (true);
}

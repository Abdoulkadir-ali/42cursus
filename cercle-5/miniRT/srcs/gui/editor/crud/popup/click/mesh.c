/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	o;
	int		bw;
	int		modal_h;

	modal_h = POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36;
	o = vec2i((gui->win.disp_size.x - POPUP_W) / 2,
			(gui->win.disp_size.y - modal_h) / 2);
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	if (phit(mouse, vec2i(o.x + POPUP_PAD, o.y + 36 + POPUP_PAD),
			vec2i(bw, POPUP_ITEM_H)))
		gui->crud.popup = POPUP_MESH_PATH;
	if (phit(mouse, vec2i(o.x + POPUP_PAD * 2 + bw, o.y + 36 + POPUP_PAD),
			vec2i(bw, POPUP_ITEM_H)))
		gui->crud.popup = POPUP_MESH_PATH;
	return (true);
}

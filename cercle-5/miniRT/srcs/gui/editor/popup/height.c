/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Recalculates the popup's centered position and total height based on 
 * its current state. Updates the values directly in gui->crud structures.
 */
void	update_popup_rect(t_gui *gui)
{
	t_crud_ui	*c;
	int			w;
	int			h;

	c = gui->crud;
	w = POPUP_W;
	if (c->popup == POPUP_SHAPE)
		h = POPUP_PAD * 2 + POPUP_TITLE_H + 4 * (POPUP_ITEM_H + 8) + 40;
	else if (c->popup == POPUP_MESH_FMT)
		h = POPUP_PAD * 2 + POPUP_TITLE_H + POPUP_ITEM_H
			+ POPUP_ERR_H + POPUP_BTN_H;
	else if (c->popup == POPUP_MESH_PATH)
		h = POPUP_PAD * 2 + POPUP_TITLE_H + POPUP_FMT_H + POPUP_ITEM_H
			+ POPUP_ERR_H + POPUP_BTN_H;
	else
		h = 0;
	c->box.pos.x = (gui->win.disp_size.x - w) / 2;
	c->box.pos.y = (gui->win.disp_size.y - h) / 2;
	c->box.size.x = w;
	c->box.size.y = h;
}

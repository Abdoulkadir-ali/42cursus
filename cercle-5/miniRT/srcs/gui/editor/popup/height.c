/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

/**
 * @brief Recalculates the popup's centered position and total height based on 
 * its current state. Updates the values directly in gui->crud structures.
 */
void	update_popup_rect(t_gui *gui)
{
	t_crud_ui	*c;

	c = &gui->crud;
	c->w = POPUP_W;
	if (c->popup == POPUP_SHAPE)
		c->h = POPUP_PAD * 2 + POPUP_TITLE_H + 4 * (POPUP_ITEM_H + 8) + 40;
	else if (c->popup == POPUP_MESH_FMT)
		c->h = POPUP_PAD * 2 + POPUP_TITLE_H + POPUP_ITEM_H
			+ POPUP_ERR_H + POPUP_BTN_H;
	else if (c->popup == POPUP_MESH_PATH)
		c->h = POPUP_PAD * 2 + POPUP_TITLE_H + POPUP_FMT_H + POPUP_ITEM_H
			+ POPUP_ERR_H + POPUP_BTN_H;
	else
		c->h = 0;
	c->pos.x = (gui->win.disp_w - c->w) / 2;
	c->pos.y = (gui->win.disp_h - c->h) / 2;
}

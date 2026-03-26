/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

/**
 * @brief Main dispatcher for drawing the active popup modal step.
 * @param gui Pointer to the GUI context.
 */
void	draw_popup(t_gui *gui)
{
	if (gui->crud.popup == POPUP_NONE)
		return ;
	update_popup_rect(gui);
	if (gui->crud.popup == POPUP_SHAPE)
		draw_popup_shape(gui);
	else if (gui->crud.popup == POPUP_MESH_FMT)
		draw_popup_mesh_fmt(gui);
	else if (gui->crud.popup == POPUP_MESH_PATH)
		draw_popup_mesh_path(gui);
}


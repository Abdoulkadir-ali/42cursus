/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
/**
 * @brief Main dispatcher for handling mouse clicks on popup modals.
 * @param gui Pointer to the GUI context.
 * @param mouse The click coordinates.
 * @return true if handled.
 */
bool	popup_handle_click(t_gui *gui, t_vec2i mouse)
{
	if (gui->crud.popup == POPUP_NONE)
		return (false);
	update_popup_rect(gui);
	if (gui->crud.popup == POPUP_SHAPE)
		return (click_popup_shape(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_FMT)
		return (click_popup_mesh_fmt(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_PATH)
		return (click_popup_mesh_path(gui, mouse));
	return (false);
}


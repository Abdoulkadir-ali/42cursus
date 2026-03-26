/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Validates the input path and triggers the appropriate mesh loader.
 * @param gui Pointer to the GUI context.
 */
void	popup_load_mesh(t_gui *gui)
{
	if (gui->crud->path_len == 0 || access(gui->crud->path_buf, R_OK) != 0)
	{
		gui->crud->path_error = true;
		gui->render.dirty = true;
		return ;
	}
	if (gui->crud->mesh_fmt == MESH_FMT_OBJ)
		editor_add_obj(gui, gui->crud->path_buf);
	else
		editor_add_glb(gui, gui->crud->path_buf);
	gui->crud->popup = POPUP_NONE;
	gui->crud->path_error = false;
	gui->render.dirty = true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	handle_input_key(t_gui *gui, int keycode)
{
	char	ch;

	if (keycode == XK_BackSpace)
	{
		if (gui->crud->path_len > 0)
			gui->crud->path_buf[--gui->crud->path_len] = '\0';
	}
	else if (keycode >= 32 && keycode <= 126
		&& gui->crud->path_len < (int)(sizeof(gui->crud->path_buf) - 1))
	{
		if (gui->crud->shift_held)
			ch = popup_shift_char(keycode);
		else
			ch = (char)keycode;
		if (ch)
		{
			gui->crud->path_buf[gui->crud->path_len++] = ch;
			gui->crud->path_buf[gui->crud->path_len] = '\0';
		}
	}
	gui->crud->path_error = false;
	gui->render.dirty = true;
}

/**
 * @brief Handles keyboard input for textual entry within popups (paths).
 * @param gui Pointer to the GUI context.
 * @param keycode The keysym received.
 * @return true if handled.
 */
bool	popup_handle_key(t_gui *gui, int keycode)
{
	if (gui->crud->popup != POPUP_MESH_PATH)
		return (false);
	if (keycode == XK_Escape)
	{
		gui->crud->popup = POPUP_NONE;
		gui->render.dirty = true;
		return (true);
	}
	if (keycode == XK_Return)
	{
		popup_load_mesh(gui);
		return (true);
	}
	handle_input_key(gui, keycode);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"
#include <unistd.h>

void	popup_load_mesh(t_gui *gui)
{
	if (gui->crud.path_len == 0
		|| access(gui->crud.path_buf, R_OK) != 0)
	{
		gui->crud.path_error = true;
		gui->render.dirty = true;
		return ;
	}
	if (gui->crud.mesh_fmt == MESH_FMT_OBJ)
		editor_add_obj(gui, gui->crud.path_buf);
	else
		editor_add_glb(gui, gui->crud.path_buf);
	gui->crud.popup = POPUP_NONE;
	gui->crud.path_error = false;
	gui->render.dirty = true;
}

void	popup_submit_tex(t_gui *gui)
{
	if (gui->crud.path_len == 0)
	{
		gui->crud.path_error = true;
		gui->render.dirty = true;
		return ;
	}
	tex_apply_from_path(gui, gui->crud.path_buf);
	if (gui->tex_status == 2)
	{
		gui->crud.path_error = true;
		gui->render.dirty = true;
	}
	else
	{
		gui->crud.popup = POPUP_NONE;
		gui->crud.path_error = false;
		gui->render.dirty = true;
	}
}

static char	popup_shift_char(int k)
{
	if (k >= 'a' && k <= 'z')
		return ((char)(k - 32));
	if (k == ':')
		return ('/');
	if (k == ';')
		return ('.');
	if (k == '.')
		return ('>');
	if (k == ',')
		return ('<');
	if (k == '-')
		return ('_');
	return ((char)k);
}

static void	handle_path_input(t_gui *gui, int k)
{
	char	ch;

	if (k == XK_BackSpace && gui->crud.path_len > 0)
	{
		gui->crud.path_buf[--gui->crud.path_len] = '\0';
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return ;
	}
	if (k >= 32 && k <= 126 && gui->crud.path_len < 255)
	{
		if (gui->crud.shift_held)
			ch = popup_shift_char(k);
		else
			ch = (char)k;
		if (ch)
		{
			gui->crud.path_buf[gui->crud.path_len++] = ch;
			gui->crud.path_buf[gui->crud.path_len] = '\0';
			gui->crud.path_error = false;
			gui->render.dirty = true;
		}
	}
}

bool	popup_handle_key(t_gui *gui, int k)
{
	if (gui->crud.popup == POPUP_NONE)
		return (false);
	if (k == XK_Escape)
	{
		gui->crud.popup = POPUP_NONE;
		gui->crud.path_error = false;
		return (gui->render.dirty = true, true);
	}
	if (gui->crud.popup != POPUP_MESH_PATH && gui->crud.popup != POPUP_TEX_PATH)
		return (true);
	if (k == XK_Return)
	{
		if (gui->crud.popup == POPUP_MESH_PATH)
			popup_load_mesh(gui);
		else
			popup_submit_tex(gui);
	}
	else
		handle_path_input(gui, k);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:07:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"
#include <unistd.h>

/*
** popup_load_mesh: validates path and loads the mesh (OBJ or GLB).
*/
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

/*
** popup_submit_tex: validate and load the texture from typed path.
*/
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

/*
** Map an unshifted keysym to its Shift-level character.
** X11/MLX delivers level-0 (unshifted) keysyms, so we do this ourselves.
** Covers lowercase->uppercase and AZERTY shifted symbols needed in paths.
*/
static char	popup_shift_char(int keycode)
{
	if (keycode >= 'a' && keycode <= 'z')
		return ((char)(keycode - 32));
	if (keycode == ':')
		return ('/');
	if (keycode == ';')
		return ('.');
	if (keycode == '.')
		return ('>');
	if (keycode == ',')
		return ('<');
	if (keycode == '-')
		return ('_');
	return ((char)keycode);
}

bool	popup_handle_key(t_gui *gui, int keycode)
{
	char	ch;

	if (gui->crud.popup == POPUP_NONE)
		return (false);
	if (keycode == XK_Escape)
	{
		gui->crud.popup = POPUP_NONE;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (gui->crud.popup != POPUP_MESH_PATH
		&& gui->crud.popup != POPUP_TEX_PATH)
		return (true);
	if (keycode == XK_Return)
	{
		if (gui->crud.popup == POPUP_MESH_PATH)
			popup_load_mesh(gui);
		else
			popup_submit_tex(gui);
		return (true);
	}
	if (keycode == XK_BackSpace)
	{
		if (gui->crud.path_len > 0)
			gui->crud.path_buf[--gui->crud.path_len] = '\0';
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (keycode >= 32 && keycode <= 126
		&& gui->crud.path_len < sizeof(gui->crud.path_buf) - 1)
	{
		if (gui->crud.shift_held)
			ch = popup_shift_char(keycode);
		else
			ch = (char)keycode;
		if (ch)
		{
			gui->crud.path_buf[gui->crud.path_len++] = ch;
			gui->crud.path_buf[gui->crud.path_len] = '\0';
			gui->crud.path_error = false;
			gui->render.dirty = true;
		}
		return (true);
	}
	return (true);
}

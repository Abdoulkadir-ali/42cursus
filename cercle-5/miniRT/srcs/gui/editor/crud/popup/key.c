/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:58:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"

bool	popup_handle_key(t_gui *gui, int keycode)
{
	if (gui->crud.popup == POPUP_NONE)
		return (false);
	if (keycode == XK_Escape)
	{
		gui->crud.popup = POPUP_NONE;
		gui->render.dirty = true;
	}
	return (true);
}

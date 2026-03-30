/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:46:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

bool	slider_handle_click(t_gui *gui, t_widget *w, t_vec2i mouse)
{
	if (mouse.x < w->pos.x || mouse.x >= w->pos.x + w->size.x)
		return (false);
	if (mouse.y < w->pos.y || mouse.y >= w->pos.y + w->size.y)
		return (false);
	slider_begin_drag(gui, w, mouse.x);
	return (true);
}

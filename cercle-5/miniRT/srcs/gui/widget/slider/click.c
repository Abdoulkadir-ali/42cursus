/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

bool	slider_handle_click(t_gui *gui, t_widget *w, t_vec2i mouse)
{
	int	ex;
	int	ey;

	ex = w->pos.x + w->size.x;
	ey = w->pos.y + w->size.y;
	if (mouse.x < w->pos.x || mouse.x >= ex)
		return (false);
	if (mouse.y < w->pos.y || mouse.y >= ey)
		return (false);
	slider_begin_drag(gui, w, mouse.x);
	return (true);
}

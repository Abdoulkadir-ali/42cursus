/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:46:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

void	update_inline_drag(t_gui *gui, int mouse_x)
{
	double	frac;
	int		rx;
	int		tx;
	int		tw;

	if (!gui->slider_state.dragging || !gui->slider_state.value_ptr)
		return ;
	tx = gui->slider_state.track_x;
	tw = gui->slider_state.track_w;
	rx = mouse_x - tx;
	if (rx < 0)
		rx = 0;
	if (rx > tw)
		rx = tw;
	frac = (double)rx / (double)tw;
	*gui->slider_state.value_ptr = gui->slider_state.dmin + frac
		* (gui->slider_state.dmax - gui->slider_state.dmin);
	if (gui->slider_state.on_change)
		gui->slider_state.on_change(gui);
	gui->render.dirty = true;
}

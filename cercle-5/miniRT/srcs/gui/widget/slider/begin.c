/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	slider_begin_drag(t_gui *gui, t_widget *w, int mouse_x)
{
    gui->slider_state.dragging = true;
    gui->slider_state.target = w;
    gui->slider_state.drag_start_x = mouse_x;
    gui->slider_state.drag_start_val = w->dvalue;
}

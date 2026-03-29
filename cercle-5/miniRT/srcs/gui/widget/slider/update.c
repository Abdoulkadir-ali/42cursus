/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	slider_update_drag(t_gui *gui, int mouse_x)
{
    t_widget *w;
    double range;
    double delta;
    double newval;

    if (!gui->slider_state->dragging || !gui->slider_state->target)
        return ;
    w = gui->slider_state->target;
    range = w->dmax - w->dmin;
    delta = (double)(mouse_x - gui->slider_state->drag_start_x)
        * range / (double)w->box.size.x;
    newval = gui->slider_state->drag_start_val + delta;
    if (newval < w->dmin)
        newval = w->dmin;
    if (newval > w->dmax)
        newval = w->dmax;
    w->dvalue = newval;
    if (w->target)
        *(double *)w->target = newval;
    if (w->on_change)
        w->on_change(w, gui);
    gui->render.dirty = true;
}

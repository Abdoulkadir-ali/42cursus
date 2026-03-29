/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:56:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse)
{
    t_widget *w;

    (void)button;
    w = gui->widgets;
    while (w)
    {
        if (mouse.x >= w->box.pos.x && mouse.x < w->box.pos.x + w->box.size.x
            && mouse.y >= w->box.pos.y && mouse.y < w->box.pos.y + w->box.size.y)
        {
            if (w->on_click)
                w->on_click(w, gui);
        }
        w = w->next;
    }
}

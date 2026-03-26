/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
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

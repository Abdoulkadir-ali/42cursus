/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:52:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_widget	*widget_create_type_pos(t_widget_type type, t_vec2i pos)
{
    t_widget *widget;

    widget = malloc(sizeof(t_widget));
    if (!widget)
        return (NULL);
    memset(widget, 0, sizeof(t_widget));
    widget->type = type;
    widget->pos = pos;
    return (widget);
}

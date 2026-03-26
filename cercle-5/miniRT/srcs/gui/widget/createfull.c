/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createfull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:56:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <string.h>
#include <stdlib.h>

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2i size,
            const char *label)
{
    t_widget *widget;

    widget = malloc(sizeof(t_widget));
    if (!widget)
        return (NULL);
    memset(widget, 0, sizeof(t_widget));
    widget->type = type;
    widget->pos = pos;
    widget->size = size;
    if (label)
        widget->label = strdup(label);
    return (widget);
}

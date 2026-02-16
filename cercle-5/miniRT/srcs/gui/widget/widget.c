/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/16 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <stdlib.h>
#include <string.h>

t_widget *widget_create(t_widget_type type, int x, int y, int width, int height, const char *label)
{
    t_widget *widget = malloc(sizeof(t_widget));
    if (!widget)
        return (NULL);
    memset(widget, 0, sizeof(t_widget));
    widget->type = type;
    widget->x = x;
    widget->y = y;
    widget->w = width;
    widget->h = height;
    if (label)
        widget->label = strdup(label);
    return (widget);
}

void widget_add(t_gui *gui, t_widget *widget)
{
    widget->next = gui->widgets;
    gui->widgets = widget;
}

void widget_draw_checkbox(t_gui *gui, t_widget *w)
{
    char buf[128];
    snprintf(buf, sizeof(buf), "[ %c ] %s", w->value ? 'X' : ' ', w->label ? w->label : "");
    mlx_string_put(gui->win.mlx, gui->win.win, w->x, w->y + w->h/2, COL_TEXT, buf);
}

void widget_draw_label(t_gui *gui, t_widget *w)
{
    mlx_string_put(gui->win.mlx, gui->win.win, w->x, w->y + w->h/2, COL_TEXT, w->label ? w->label : "");
}

void widget_draw_all(t_gui *gui)
{
    t_widget *w = gui->widgets;
    while (w) {
        if (w->type == WIDGET_CHECKBOX) widget_draw_checkbox(gui, w);
        else if (w->type == WIDGET_LABEL) widget_draw_label(gui, w);
        // ... add more types
        w = w->next;
    }
}

void widget_handle_mouse(t_gui *gui, int button, int x, int y)
{
    t_widget *w = gui->widgets;
    while (w) {
        if (x >= w->x && x <= w->x + w->w && y >= w->y && y <= w->y + w->h) {
            if (button == Button1 && w->on_click) w->on_click(w, gui);
        }
        w = w->next;
    }
}

void widget_handle_key(t_gui *gui, int keycode)
{
    (void)keycode;
    t_widget *w = gui->widgets;
    while (w) {
        if (w->on_change) w->on_change(w, gui);
        w = w->next;
    }
}

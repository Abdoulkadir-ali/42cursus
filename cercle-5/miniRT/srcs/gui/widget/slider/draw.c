/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:53:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_slider_track(t_gui *gui, t_widget *w)
{
    t_panel track;
    t_panel fill;
    double frac;
    int fill_w;

    frac = 0.0;
    if (w->dmax > w->dmin)
        frac = (w->dvalue - w->dmin) / (w->dmax - w->dmin);
    if (frac < 0.0)
        frac = 0.0;
    if (frac > 1.0)
        frac = 1.0;
    fill_w = (int)(frac * w->box.size.x);
    track = (t_panel){.box = (t_gui_box){vec2i(w->box.pos.x, w->box.pos.y + w->box.size.y / 2 - 3), vec2i(w->box.size.x, 6)}, .bg = COL_SLIDER_BG, .brd = COL_BORDER};
    draw_panel(gui, track);
    if (fill_w > 0)
    {
        fill = (t_panel){.box = (t_gui_box){vec2i(w->box.pos.x, w->box.pos.y + w->box.size.y / 2 - 3), vec2i(fill_w, 6)}, .bg = COL_SLIDER_FG, .brd = COL_SLIDER_FG};
        draw_panel(gui, fill);
    }
}

static void	draw_slider_label(t_gui *gui, t_widget *w)
{
    char buf[64];

    if (w->label)
        gui_draw_string(gui, w->label, w->box.pos.x, w->box.pos.y + 2, COL_TEXT);
    snprintf(buf, sizeof(buf), "%.3f", w->dvalue);
    gui_draw_string(gui, buf, w->box.pos.x + w->box.size.x - 48, w->box.pos.y + 2, COL_HOVER);
}

void	widget_draw_slider(t_gui *gui, t_widget *w)
{
    draw_slider_track(gui, w);
    draw_slider_label(gui, w);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

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
    fill_w = (int)(frac * w->size.x);
    track = (t_panel){.x = w->pos.x, .y = w->pos.y + w->size.y / 2 - 3,
        .w = w->size.x, .h = 6, .bg = COL_SLIDER_BG, .brd = COL_BORDER,
        .pos = w->pos, .size = vec2i(w->size.x, 6)};
    draw_panel(gui, track);
    if (fill_w > 0)
    {
        fill = (t_panel){.x = w->pos.x, .y = w->pos.y + w->size.y / 2 - 3,
            .w = fill_w, .h = 6, .bg = COL_SLIDER_FG, .brd = COL_SLIDER_FG,
            .pos = w->pos, .size = vec2i(fill_w, 6)};
        draw_panel(gui, fill);
    }
}

static void	draw_slider_label(t_gui *gui, t_widget *w)
{
    char buf[64];

    if (w->label)
        mlx_string_put(gui->win.mlx, gui->win.win,
            w->pos.x, w->pos.y + 2, COL_TEXT, w->label);
    snprintf(buf, sizeof(buf), "%.3f", w->dvalue);
    mlx_string_put(gui->win.mlx, gui->win.win,
        w->pos.x + w->size.x - 48, w->pos.y + 2, COL_HOVER, buf);
}

void	widget_draw_slider(t_gui *gui, t_widget *w)
{
    draw_slider_track(gui, w);
    draw_slider_label(gui, w);
}

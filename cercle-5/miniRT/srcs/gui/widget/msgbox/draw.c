/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:46:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_msgbox_bg(t_gui *gui, t_widget *w)
{
	t_panel	overlay;
	t_panel	box;

	overlay = (t_panel){.pos = vec2i(0, 0), .size = gui->win.disp_size,
		.bg = 0x000000, .brd = 0x000000};
	draw_panel(gui, overlay);
	box = (t_panel){.pos = w->pos, .size = w->size,
		.bg = 0x12121E, .brd = COL_ACCENT};
	draw_panel(gui, box);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x + 8, (int)w->pos.y + 8), COL_ACCENT);
	if (w->msg_text)
		gui_draw_string(gui, w->msg_text,
			vec2i(w->pos.x + 8, (int)w->pos.y + 32), COL_TEXT);
}

static void	draw_msgbox_btn(t_gui *gui, t_widget *w, int bw, int by, int i)
{
	t_panel	btn;
	int		bx;

	bx = (int)w->pos.x + 8 + i * (bw + 4);
	btn = (t_panel){.pos = vec2i(bx, by), .size = vec2i(bw - 4, 22),
		.bg = 0x2A2A40, .brd = COL_BORDER};
	draw_panel(gui, btn);
	if (w->btn_labels[i])
		gui_draw_string(gui, w->btn_labels[i],
			vec2i(bx + bw / 2 - (int)ft_strlen(w->btn_labels[i]) * 4,
				by + 7), COL_TEXT);
}

void	widget_draw_msgbox(t_gui *gui, t_widget *w)
{
	int	bw;
	int	by;
	int	i;

	draw_msgbox_bg(gui, w);
	bw = w->size.x - 16;
	if (w->btn_count > 0)
		bw /= w->btn_count;
	by = (int)w->pos.y + w->size.y - 28;
	i = 0;
	while (i < w->btn_count)
		draw_msgbox_btn(gui, w, bw, by, i++);
}

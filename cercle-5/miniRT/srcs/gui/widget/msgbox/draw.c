/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_msgbox_bg(t_gui *gui, t_widget *w)
{
	t_panel	overlay;
	t_panel	box;

	overlay.pos = vec2i(0, 0);
	overlay.size = gui->win.disp_size;
	overlay.bg = 0x000000;
	overlay.brd = 0x000000;
	draw_panel(gui, overlay);
	box.pos = w->pos;
	box.size = w->size;
	box.bg = 0x12121E;
	box.brd = COL_ACCENT;
	draw_panel(gui, box);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x + 8, w->pos.y + 8), COL_ACCENT);
	if (w->msg_text)
		gui_draw_string(gui, w->msg_text,
			vec2i(w->pos.x + 8, w->pos.y + 32), COL_TEXT);
}

static void	draw_msgbox_btn(t_gui *gui, t_widget *w, t_vec3i p)
{
	t_panel	btn;
	int		bx;

	bx = w->pos.x + 8 + p.z * (p.x + 4);
	btn.pos = vec2i(bx, p.y);
	btn.size = vec2s(p.x - 4, 22);
	btn.bg = 0x2A2A40;
	btn.brd = COL_BORDER;
	draw_panel(gui, btn);
	if (w->btn_labels[p.z])
		gui_draw_string(gui, w->btn_labels[p.z],
			vec2i(bx + p.x / 2 - ft_strlen(w->btn_labels[p.z]) * 4,
				p.y + 7), COL_TEXT);
}

void	widget_draw_msgbox(t_gui *gui, t_widget *w)
{
	t_vec3i	p;

	draw_msgbox_bg(gui, w);
	int		bc;

	p.x = w->size.x - 16;
	if (w->btn_count > 0)
		p.x /= w->btn_count;
	p.y = w->pos.y + w->size.y - 28;
	p.z = 0;
	bc = w->btn_count;
	while (p.z < bc)
	{
		draw_msgbox_btn(gui, w, p);
		p.z++;
	}
}

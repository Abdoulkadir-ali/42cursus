/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_btn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_slot_btn(t_gui *gui, t_panel btn, bool active)
{
	t_vec2i	lpos;
	t_vec2s	d;
	int		col_txt;

	d = gui->win.disp_size;
	if (active)
		btn.bg = COL_ACCENT;
	else
		btn.bg = 0x2A2A40;
	btn.brd = COL_BORDER;
	draw_panel(gui, btn);
	lpos = vec2i(btn.pos.x + (int)btn.size.x / 2 - (int)ft_strlen(btn.lbl) * 4,
			btn.pos.y + ui_sy(5, d));
	col_txt = COL_TEXT;
	if (active)
		col_txt = COL_BG;
	gui_draw_string(gui, (char *)btn.lbl, lpos, col_txt);
}

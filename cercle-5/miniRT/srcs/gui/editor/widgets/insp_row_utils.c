/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_row_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_insp_header(t_gui *gui, t_vec2i pos, const char *title)
{
	t_vec2s	d;
	t_panel	sep;

	d = gui->win.disp_size;
	gui_draw_string(gui, title, pos, COL_ACCENT);
	sep = (t_panel){
		.pos = vec2i(pos.x, pos.y + ui_sy(INSP_HDR_STEP - 3, d)),
		.size = ui_size(INSP_IN_OFF + INSP_IN_W, 1, d),
		.bg = COL_BORDER, .brd = COL_BORDER};
	draw_panel(gui, sep);
}

void	draw_panel_insp_rows(t_gui *gui, t_islider *sl, size_t n, t_vec2i pos)
{
	t_vec2s	d;
	size_t	i;

	d = gui->win.disp_size;
	i = 0;
	while (i < n)
	{
		draw_insp_row(gui, pos, sl[i]);
		pos.y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
}

bool	insp_toggle_click(t_gui *gui, t_vec2i mouse, t_vec2i pos)
{
	t_vec2s	d;
	int		ix;

	d = gui->win.disp_size;
	ix = pos.x + ui_sx(INSP_IN_OFF, d);
	return (mouse.x >= ix && mouse.x < ix + ui_sx(INSP_IN_W, d)
		&& mouse.y >= pos.y
		&& mouse.y < pos.y + ui_sy(INSP_ROW_STEP, d));
}

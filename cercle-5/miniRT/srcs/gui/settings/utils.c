/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:42:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

/*
** Draws a labeled ON/OFF radio row.
** The toggle button is right-aligned inside a band of width w.
*/
void	draw_radio_row(t_gui *gui, t_panel pan, t_iradio r)
{
	int			btn_x;
	int			bg;
	int			col;
	const char	*status;

	btn_x = pan.pos.x + pan.size.x - 44 - 4;
	bg = COL_RADIO_OFF_BG;
	col = COL_RADIO_OFF_TEXT;
	status = "OFF";
	if (*r.ptr)
	{
		bg = COL_RADIO_ON_BG;
		col = COL_RADIO_ON_TEXT;
		status = "ON";
	}
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		pan.pos.x + 8, pan.pos.y + 15, COL_TEXT, (char *)r.label);
	draw_panel(gui, (t_panel){vec2i(btn_x, pan.pos.y + 4),
		vec2s(44, 20), bg, col, ""});
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		btn_x + 10, pan.pos.y + 18, col, (char *)status);
}

static void	draw_s_slider_rects(t_gui *gui, t_vec2i pos, int tw, int fw)
{
	int	kx;

	fill_rect(gui, vec2i(pos.x, pos.y + 14), (t_vec2s){tw, 8}, COL_SLIDER_BG);
	fill_rect(gui, vec2i(pos.x, pos.y + 14), (t_vec2s){tw, 1}, COL_BORDER);
	fill_rect(gui, vec2i(pos.x, pos.y + 21), (t_vec2s){tw, 1}, COL_BORDER);
	if (fw > 0)
		fill_rect(gui, vec2i(pos.x, pos.y + 14), (t_vec2s){fw, 8},
			COL_SLIDER_FG);
	kx = pos.x + fw - 1;
	if (kx < pos.x)
		kx = pos.x;
	fill_rect(gui, vec2i(kx, pos.y + 12), (t_vec2s){3, 12}, COL_SLIDER_KNOB);
}

/*
** Draws a labeled slider row sized to the settings panel width.
*/
void	draw_settings_slider(t_gui *gui, t_vec2i pos, t_islider sl)
{
	char	buf[64];
	double	frac;
	int		fill_w;
	int		track_w;

	track_w = SETTINGS_W - 32;
	frac = 0.0;
	if (sl.max > sl.min)
		frac = (*sl.ptr - sl.min) / (sl.max - sl.min);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = (int)(frac * track_w);
	snprintf(buf, sizeof(buf), "%.3g", *sl.ptr);
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		pos.x, pos.y, COL_TEXT, (char *)sl.label);
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		pos.x + track_w - 56, pos.y, COL_HOVER, buf);
	draw_s_slider_rects(gui, pos, track_w, fill_w);
}

t_iradio	init_iradio(const char *label, bool *ptr,
		void (*on_change)(t_gui *))
{
	t_iradio	r;

	r.label = label;
	r.ptr = ptr;
	r.on_change = on_change;
	return (r);
}

void	draw_perf_tag(t_gui *gui, int x, int y, bool heavy)
{
	if (heavy)
		mlx_string_put_c(gui->win.mlx, gui->win.win, x, y, 0xFF4444, "Heavy");
	else
		mlx_string_put_c(gui->win.mlx, gui->win.win, x, y, 0x44CC44, "Fast");
}

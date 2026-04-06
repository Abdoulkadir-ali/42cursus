/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ambient_panel(t_gui *gui, t_vec2i pos)
{
	t_islider	sl[4];
	t_vec2i		p;
	t_vec2i		sw_pos;
	t_vec2s		d;

	d = gui->win.disp_size;
	p = (t_vec2i){pos.x + ui_sx(8, d), ui_sy(90, d)};
	draw_insp_header(gui, (t_vec2i){p.x, p.y}, "Ambient Light");
	sw_pos = vec2i(p.x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p.y);
	draw_insp_color_swatch(gui, sw_pos, gui->scene->ambient.rgb);
	p.y += ui_sy(INSP_HDR_STEP, d);
	get_ambient_sliders(gui->scene, sl);
	draw_panel_insp_rows(gui, sl, 4, p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_light_header(t_gui *gui, t_light *lt, t_vec2i p)
{
	const char	*type;
	t_vec2s		d;
	t_vec2i		sw;

	d = gui->win.disp_size;
	type = "Point Light";
	if (lt->type == LIGHT_SPOT)
		type = "Spot Light";
	draw_insp_header(gui, p, type);
	sw.x = p.x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d);
	sw.y = p.y;
	draw_insp_color_swatch(gui, sw, lt->rgb);
}

void	draw_light_panel(t_gui *gui, t_vec2i pos)
{
	t_light		*lt;
	t_islider	sl[5];
	t_vec2i		p;
	t_vec2s		d;
	int			count;

	if (!gui->scene || gui->selection.index.i >= gui->scene->light_count)
		return ;
	d = gui->win.disp_size;
	lt = &gui->scene->lights[gui->selection.index.i];
	p.x = pos.x + ui_sx(8, d);
	p.y = ui_sy(90, d);
	draw_light_header(gui, lt, p);
	p.y += ui_sy(INSP_HDR_STEP, d);
	build_light_sliders(lt, sl, &count);
	draw_panel_insp_rows(gui, sl, count, p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 11:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ambient_panel(t_gui *gui, t_vec2i pos)
{
	t_islider	sl[4];
	t_vec2i		p;

	p = (t_vec2i){pos.x + 8, 90};
	draw_insp_header(gui, (t_vec2i){p.x, p.y}, "Ambient Light");
	draw_insp_color_swatch(gui,
		vec2i(p.x + INSP_IN_OFF + INSP_IN_W - 18, p.y),
		gui->scene->ambient.rgb.x,
		gui->scene->ambient.rgb.y,
		gui->scene->ambient.rgb.z);
	p.y += INSP_HDR_STEP;
	get_ambient_sliders(gui->scene, sl);
	draw_panel_insp_rows(gui, sl, 4, p);
}


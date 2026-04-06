/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_swatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:01:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_insp_color_swatch(t_gui *gui, t_vec2i pos, t_vec3 rgb)
{
	t_panel	sw;
	t_vec2s	d;

	d = gui->win.disp_size;
	sw = (t_panel){.pos = pos, .size = ui_size(14, 14, d),
		.bg = pack_rgb(rgb), .brd = COL_BORDER};
	draw_panel(gui, sw);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_light_panel(t_gui *gui, t_vec2i pos)
{
	t_vec2i		d;
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	t_vec2i		p;
	const char	*type;

	d = gui->win.disp_size;
	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return ;
	lt = &gui->scene->lights[gui->selection.index];
	p = (t_vec2i){pos.x + ui_sx(8, d), ui_sy(90, d)};
	type = lt->type == LIGHT_SPOT ? "Spot Light" : "Point Light";
	draw_insp_header(gui, (t_vec2i){p.x, p.y}, type);
	draw_insp_color_swatch(gui,
		vec2i(p.x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p.y),
		lt->rgb.x, lt->rgb.y, lt->rgb.z);
	p.y += ui_sy(INSP_HDR_STEP, d);
	build_light_sliders(lt, sl, &count);
	i = 0;
	while (i < count)
	{
		draw_insp_row(gui, (t_vec2i){p.x, p.y}, sl[i]);
		p.y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
}


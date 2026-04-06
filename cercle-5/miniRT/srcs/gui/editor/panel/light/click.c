/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	t_vec2i		p;
	t_vec2s		d;
	int			count;
	int			i;

	if (!gui->scene || gui->selection.index.i >= gui->scene->light_count)
		return (false);
	d = gui->win.disp_size;
	lt = &gui->scene->lights[gui->selection.index.i];
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(90 + INSP_HDR_STEP, d);
	build_light_sliders(lt, sl, &count);
	i = 0;
	while (i < count)
	{
		if (insp_row_click(gui, mouse, p, sl[i]))
			return (true);
		p.y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

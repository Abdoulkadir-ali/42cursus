/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	t_vec2i		p;
	int			count;
	int			i;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return (false);
	lt = &gui->scene->lights[gui->selection.index];
	p.x = gui->win.disp_size.x - gui->inspector.width + ui_sx(8, gui->win.disp_size);
	p.y = ui_sy(90 + INSP_HDR_STEP, gui->win.disp_size);
	build_light_sliders(lt, sl, &count);
	i = 0;
	while (i < count)
	{
		if (insp_row_click(gui, mouse, p, sl[i]))
			return (true);
		p.y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
		i++;
	}
	return (false);
}


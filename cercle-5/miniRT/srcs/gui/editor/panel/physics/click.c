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

bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
	t_physics_body *phys)
{
	t_islider	sl[3];
	int			i;
	t_vec2i		p;

	if (!phys)
		return (false);
	p.x = gui->win.disp_size.x - gui->inspector.width + ui_sx(8, gui->win.disp_size);
	p.y = ui_sy(90 + INSP_HDR_STEP + 30 + 34 + INSP_HDR_STEP, gui->win.disp_size);
	get_phys_sliders(phys, sl);
	i = 0;
	while (i < 3)
	{
		if (insp_row_click(gui, mouse, p, sl[i]))
			return (true);
		p.y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
		i++;
	}
	if (insp_toggle_click(gui, mouse, p))
	{
		phys->is_static = !phys->is_static;
		gui->render.dirty = true;
		return (true);
	}
	return (false);
}


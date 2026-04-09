/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_vec2i	get_phys_spos(t_gui *gui)
{
	t_vec2s	d;
	t_vec2i	p;

	d = gui->win.disp_size;
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(90 + INSP_HDR_STEP + 30 + 34 + INSP_HDR_STEP, d);
	return (p);
}

bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
	t_physics_body *phys)
{
	t_islider	sl[3];
	t_vec2i		p;
	int			i;

	if (!phys)
		return (false);
	p = get_phys_spos(gui);
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
		phys->is_static = (phys->is_static == 0);
		gui->render.dirty = true;
		return (true);
	}
	return (false);
}

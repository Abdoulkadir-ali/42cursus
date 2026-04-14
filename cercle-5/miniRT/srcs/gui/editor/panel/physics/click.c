/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 03:15:00 by abdoali          ###   ########.fr       */
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

static bool	click_phys_props(t_gui *gui, t_vec2i mouse, t_vec2i *p,
		t_physics_body *phys)
{
	t_islider	sl[3];
	int			i;

	get_phys_sliders(phys, sl);
	i = 0;
	while (i < 3)
	{
		if (insp_row_click(gui, mouse, *p, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
		i++;
	}
	if (insp_toggle_click(gui, mouse, *p))
	{
		phys->is_static = (phys->is_static == 0);
		gui->render.dirty = true;
		return (true);
	}
	p->y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
	return (false);
}

bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
	t_physics_body *phys)
{
	t_islider	tsl;
	t_material	*mat;
	t_vec2i		p;

	p = get_phys_spos(gui);
	if (phys && click_phys_props(gui, mouse, &p, phys))
		return (true);
	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	p.y += ui_sy(6 + INSP_HDR_STEP, gui->win.disp_size);
	tsl = (t_islider){"Temp(K)", SL_TEMP_MIN, SL_TEMP_MAX,
		&mat->temperature, sync_temperature};
	if (insp_row_click(gui, mouse, p, tsl))
		return (true);
	p.y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
	tsl = (t_islider){"Power", SL_EM_POWER_MIN, SL_EM_POWER_MAX,
		&mat->em_intensity, sync_group_materials};
	if (insp_row_click(gui, mouse, p, tsl))
		return (true);
	return (false);
}

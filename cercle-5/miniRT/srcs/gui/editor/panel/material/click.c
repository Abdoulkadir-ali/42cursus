/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:08:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	click_mat_surface(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl[5];
	size_t		i;

	d = gui->win.disp_size;
	sl[0] = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness, sync_group_materials};
	sl[1] = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic, sync_group_materials};
	sl[2] = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency, sync_group_materials};
	sl[3] = (t_islider){"Reflect", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity, sync_group_materials};
	sl[4] = (t_islider){"IOR", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index, sync_group_materials};
	p->y += ui_sy(INSP_HDR_STEP, d);
	i = 0;
	while (i < 5)
	{
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

static bool	click_mat_albedo(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl[3];
	size_t		i;

	d = gui->win.disp_size;
	sl[0] = (t_islider){"R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x, sync_group_materials};
	sl[1] = (t_islider){"G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y, sync_group_materials};
	sl[2] = (t_islider){"B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z, sync_group_materials};
	p->y += ui_sy(6 + INSP_HDR_STEP, d);
	i = 0;
	while (i < 3)
	{
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

static bool	click_mat_emission(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl[3];
	size_t		i;

	d = gui->win.disp_size;
	sl[0] = (t_islider){"R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x, sync_group_materials};
	sl[1] = (t_islider){"G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y, sync_group_materials};
	sl[2] = (t_islider){"B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z, sync_group_materials};
	p->y += ui_sy(6 + INSP_HDR_STEP, d);
	i = 0;
	while (i < 3)
	{
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_vec2i		p;
	t_vec2s		d;

	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	d = gui->win.disp_size;
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(92, d);
	if (click_mat_surface(gui, mouse, mat, &p))
		return (true);
	if (click_mat_albedo(gui, mouse, mat, &p))
		return (true);
	if (click_mat_emission(gui, mouse, mat, &p))
		return (true);
	return (false);
}

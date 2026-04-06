/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:39:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_mat_surface_ext(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	sl = (t_islider){"Reflect", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"IOR", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	draw_mat_surface(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Surface");
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	draw_mat_surface_ext(gui, mat, p);
}

static void	draw_mat_albedo(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;
	t_vec2i		sw_pos;

	d = gui->win.disp_size;
	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Albedo");
	sw_pos = vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p->y);
	draw_insp_color_swatch(gui, sw_pos, mat->albedo_map.color_a);
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	draw_mat_emission(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;
	t_vec2i		sw_pos;

	d = gui->win.disp_size;
	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Emission");
	sw_pos = vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p->y);
	draw_insp_color_swatch(gui, sw_pos, mat->emission);
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
}

void	draw_material_panel_text(t_gui *gui, t_vec2i pos)
{
	t_material	*mat;
	t_vec2i		p;
	t_vec2s		d;

	mat = get_selected_material(gui);
	d = gui->win.disp_size;
	if (!mat)
	{
		gui_draw_string(gui, "No material", (t_vec2i){pos.x + ui_sx(8, d),
			ui_sy(92, d)}, COL_TEXT);
		return ;
	}
	p = (t_vec2i){pos.x + ui_sx(8, d), ui_sy(92, d)};
	draw_mat_surface(gui, mat, &p);
	draw_mat_albedo(gui, mat, &p);
	draw_mat_emission(gui, mat, &p);
}

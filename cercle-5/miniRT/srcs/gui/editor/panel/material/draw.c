/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:10:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_slot_btn(t_gui *gui, const char *lbl, t_vec2i pos,
		t_vec2s size, bool active);

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
	sl = (t_islider){"Shininess", SL_SHINE_MIN, SL_SHINE_MAX,
		&mat->shininess, sync_group_materials};
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

static void	draw_mat_albedo(t_gui *gui, t_material *mat, t_vec2i *p, int slot)
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
	if (slot == 3)
	{
		draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Texture");
		p->y += ui_sy(INSP_HDR_STEP, d);
		draw_slot_btn(gui, "Fill Path",
			(t_vec2i){p->x, p->y},
			vec2s(ui_sx(gui->inspector.width - 18, d), ui_sy(18, d)),
			gui->crud.popup == POPUP_TEX_PATH);
		p->y += ui_sy(24, d);
		if (gui->tex_status == 1)
			gui_draw_string(gui, gui->tex_status_msg,
				(t_vec2i){p->x, p->y}, 0x50FF80);
		else if (gui->tex_status == 2)
			gui_draw_string(gui, gui->tex_status_msg,
				(t_vec2i){p->x, p->y}, 0xFF5050);
		p->y += ui_sy(16, d);
		{
			t_texture	*tex = &mat->albedo_map;
			if (tex->addr)
			{
				draw_tex_preview(gui, (t_vec2i){p->x, p->y},
					vec2s(ui_sx(gui->inspector.width - 18, d), 72), tex);
				p->y += 72 + ui_sy(4, d);
			}
		}
		sl = (t_islider){"UV Scale", SL_TILE_MIN, SL_TILE_MAX,
			&mat->albedo_map.scale, sync_group_materials};
		draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
		p->y += ui_sy(INSP_ROW_STEP, d);
		draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Tint");
		sw_pos = vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p->y);
		draw_insp_color_swatch(gui, sw_pos, mat->albedo_map.color_a);
		p->y += ui_sy(INSP_HDR_STEP, d);
		sl = (t_islider){"Tint R", SL_COL_MIN, SL_COL_MAX,
			&mat->albedo_map.color_a.x, sync_group_materials};
		draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
		p->y += ui_sy(INSP_ROW_STEP, d);
		sl = (t_islider){"Tint G", SL_COL_MIN, SL_COL_MAX,
			&mat->albedo_map.color_a.y, sync_group_materials};
		draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
		p->y += ui_sy(INSP_ROW_STEP, d);
		sl = (t_islider){"Tint B", SL_COL_MIN, SL_COL_MAX,
			&mat->albedo_map.color_a.z, sync_group_materials};
		draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
		p->y += ui_sy(INSP_ROW_STEP, d);
		return ;
	}
	if (slot != 1)
		return ;
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Color B");
	sw_pos = vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18, d), p->y);
	draw_insp_color_swatch(gui, sw_pos, mat->albedo_map.color_b);
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"B R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.x, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.y, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.z, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Tile", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
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

static void	draw_slot_btn(t_gui *gui, const char *lbl, t_vec2i pos,
		t_vec2s size, bool active)
{
	t_panel	btn;
	t_vec2i	lpos;
	t_vec2s	d;

	d = gui->win.disp_size;
	btn = (t_panel){pos, size, active ? COL_ACCENT : 0x2A2A40,
		COL_BORDER, NULL};
	draw_panel(gui, btn);
	lpos = vec2i(pos.x + (int)size.x / 2 - (int)ft_strlen(lbl) * 4,
			pos.y + ui_sy(5, d));
	gui_draw_string(gui, (char *)lbl, lpos, active ? COL_BG : COL_TEXT);
}

static void	draw_mat_slot_buttons(t_gui *gui, t_vec2i pos, int active,
		t_vec2s d)
{
	int				bw;
	int				bh;
	int				gap;
	const char		*lbl[4];

	lbl[0] = "Origin";
	lbl[1] = "Checker";
	lbl[2] = "Solid";
	lbl[3] = "Texture";
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	bh = ui_sy(18, d);
	gap = ui_sx(3, d);
	draw_slot_btn(gui, lbl[0], pos, vec2s(bw, bh), active == 0);
	draw_slot_btn(gui, lbl[1], vec2i(pos.x + bw + gap, pos.y),
		vec2s(bw, bh), active == 1);
	draw_slot_btn(gui, lbl[2], vec2i(pos.x, pos.y + bh + gap),
		vec2s(bw, bh), active == 2);
	draw_slot_btn(gui, lbl[3], vec2i(pos.x + bw + gap, pos.y + bh + gap),
		vec2s(bw, bh), active == 3);
}

static void	draw_fdf_mode_row(t_gui *gui, t_vec2i pos, t_vec2s d)
{
	t_mesh		*fdf;
	t_fdf_state	*state;
	int			bw;
	int			gap;
	t_fdf_mode	cur;

	fdf = get_selected_fdf_mesh(gui);
	if (!fdf)
		return ;
	state = (t_fdf_state *)fdf->extra;
	cur = state ? state->mode : FDF_MODE_HEIGHT;
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	gap = ui_sx(3, d);
	draw_insp_header(gui, pos, "FDF Mode");
	pos.y += ui_sy(INSP_HDR_STEP, d);
	draw_slot_btn(gui, "Heightmap", pos,
		vec2s(bw, ui_sy(18, d)), cur == FDF_MODE_HEIGHT);
	draw_slot_btn(gui, "Picture",
		vec2i(pos.x + bw + gap, pos.y),
		vec2s(bw, ui_sy(18, d)), cur == FDF_MODE_PICTURE);
}

void	draw_material_panel_text(t_gui *gui, t_vec2i pos)
{
	t_material	*mat;
	t_vec2i		p;
	t_vec2s		d;
	int			slot;

	mat = get_selected_material(gui);
	d = gui->win.disp_size;
	p = (t_vec2i){pos.x + ui_sx(8, d), ui_sy(92, d)};
	slot = get_selected_group_slot(gui);
	if (gui->tex_popup_input)
		gui->tex_popup_input->visible = (slot == 3 && gui->selection.active);
	draw_mat_slot_buttons(gui, p, slot, d);
	p.y += ui_sy(44, d);
	draw_fdf_mode_row(gui, p, d);
	if (get_selected_fdf_mesh(gui))
		p.y += ui_sy(INSP_HDR_STEP + 26, d);
	if (!mat)
	{
		if (slot == 3)
			gui_draw_string(gui, "No texture — click Texture to load",
				(t_vec2i){p.x, p.y}, COL_TEXT);
		return ;
	}
	draw_mat_surface(gui, mat, &p);
	draw_mat_albedo(gui, mat, &p, slot);
	draw_mat_emission(gui, mat, &p);
}

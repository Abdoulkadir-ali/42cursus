/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_albedo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_slot_btn(t_gui *gui, t_panel btn, bool active);

static void	draw_tex_status(t_gui *gui, t_vec2i *p, t_vec2s d)
{
	int		col;

	if (gui->tex_status == 1)
		col = 0x50FF80;
	else
		col = 0xFF5050;
	if (gui->tex_status != 0)
	{
		gui_draw_string(gui, gui->tex_status_msg, (t_vec2i){p->x, p->y}, col);
		p->y += ui_sy(16, d);
	}
}

static void	draw_albedo_tex(t_gui *gui, t_material *mat, t_vec2i *p, t_vec2s d)
{
	t_islider	sl;
	t_vec2s		s;

	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Texture");
	p->y += ui_sy(INSP_HDR_STEP, d);
	s = vec2s(ui_sx(gui->inspector.width - 18, d), ui_sy(18, d));
	draw_slot_btn(gui, (t_panel){(t_vec2i){p->x, p->y}, s, 0, 0, "Fill Path"},
		gui->crud.popup == POPUP_TEX_PATH);
	p->y += ui_sy(24, d);
	draw_tex_status(gui, p, d);
	if (mat->albedo_map.addr)
	{
		draw_tex_preview(gui, (t_vec2i){p->x, p->y},
			vec2s(ui_sx(gui->inspector.width - 18, d), 72), &mat->albedo_map);
		p->y += 72 + ui_sy(4, d);
	}
	sl = (t_islider){"UV Scale", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	draw_albedo_checker(t_gui *gui, t_material *mat, t_vec2i *p,
		t_vec2s d)
{
	t_islider	sl;
	t_vec2i		sw_pos;

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
	sl = (t_islider){"Tile", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

void	draw_mat_albedo(t_gui *gui, t_material *mat, t_vec2i *p, int slot)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Albedo");
	draw_insp_color_swatch(gui, vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W - 18,
				d), p->y), mat->albedo_map.color_a);
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
		draw_albedo_tex(gui, mat, p, d);
	else if (slot == 1)
		draw_albedo_checker(gui, mat, p, d);
}

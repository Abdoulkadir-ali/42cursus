/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albedo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:10:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	click_albedo_texture(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;
	t_texture	*tex;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP, d);
	if (mat_hit_btn(gui, mouse, *p,
			vec2s(ui_sx(gui->inspector.width - 18, d), ui_sy(18, d))))
	{
		gui->crud.popup = POPUP_TEX_PATH;
		gui->crud.path_buf[0] = '\0';
		gui->crud.path_len = 0;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	p->y += ui_sy(24, d);
	p->y += ui_sy(16, d);
	tex = &mat->albedo_map;
	if (tex->addr)
		p->y += 72 + ui_sy(4, d);
	sl = (t_islider){"UV Scale", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"Tint R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Tint G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Tint B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	return (false);
}

static bool	click_albedo_checker(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"B R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.x, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.y, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_b.z, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Tile", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	return (false);
}

bool	click_mat_albedo(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;
	int			slot;

	d = gui->win.disp_size;
	slot = get_selected_group_slot(gui);
	p->y += ui_sy(6 + INSP_HDR_STEP, d);
	sl = (t_islider){"R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	if (slot == 3)
		return (click_albedo_texture(gui, mouse, mat, p));
	if (slot == 1)
		return (click_albedo_checker(gui, mouse, mat, p));
	return (false);
}

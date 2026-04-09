/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albedo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	click_rgb(t_gui *gui, t_vec2i mouse, t_vec3 *v, t_vec2i *p)
{
	t_islider	sl;
	t_vec2s		d;
	int			i;
	double		*ptr[3];
	const char	*lbl[3] = {"R", "G", "B"};

	d = gui->win.disp_size;
	ptr[0] = &v->x;
	ptr[1] = &v->y;
	ptr[2] = &v->z;
	i = 0;
	while (i < 3)
	{
		sl = (t_islider){lbl[i], SL_COL_MIN, SL_COL_MAX, ptr[i],
			sync_group_materials};
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

static bool	click_albedo_texture(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP, d);
	if (mat_hit_btn(gui, mouse, *p,
			vec2s(ui_sx(gui->inspector.width - 18, d), ui_sy(18, d))))
	{
		gui->crud.popup = POPUP_TEX_PATH;
		return (gui->render.dirty = true, true);
	}
	p->y += ui_sy(24 + 16, d);
	if (mat->albedo_map.addr)
		p->y += 72 + ui_sy(4, d);
	sl = (t_islider){"UV Scale", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP + INSP_HDR_STEP, d);
	return (click_rgb(gui, mouse, &mat->albedo_map.color_a, p));
}

static bool	click_albedo_checker(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_islider	sl;
	t_vec2s		d;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP, d);
	if (click_rgb(gui, mouse, &mat->albedo_map.color_b, p))
		return (true);
	sl = (t_islider){"Tile", SL_TILE_MIN, SL_TILE_MAX,
		&mat->albedo_map.scale, sync_group_materials};
	return (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl));
}

bool	click_mat_albedo(t_gui *gui, t_vec2i mouse, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	int			slot;

	d = gui->win.disp_size;
	slot = get_selected_group_slot(gui);
	p->y += ui_sy(6 + INSP_HDR_STEP, d);
	if (click_rgb(gui, mouse, &mat->albedo_map.color_a, p))
		return (true);
	if (slot == 3)
		return (click_albedo_texture(gui, mouse, mat, p));
	if (slot == 1)
		return (click_albedo_checker(gui, mouse, mat, p));
	return (false);
}

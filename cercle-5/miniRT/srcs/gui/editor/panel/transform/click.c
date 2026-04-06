/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:42:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	try_tr_pos(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	sl = (t_islider){"X", SL_POS_MIN, SL_POS_MAX, &gui->transform.pos.x,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Y", SL_POS_MIN, SL_POS_MAX, &gui->transform.pos.y,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Z", SL_POS_MIN, SL_POS_MAX, &gui->transform.pos.z,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	return (false);
}

static bool	try_tr_rot(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP + 6, d);
	sl = (t_islider){"Pitch", -180.0, 180.0, &gui->transform.rotation.pitch,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Yaw", -180.0, 180.0, &gui->transform.rotation.yaw,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Roll", -180.0, 180.0, &gui->transform.rotation.roll,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	return (false);
}

static bool	try_tr_scale(t_gui *gui, t_vec2i mouse, t_vec2i *p, float max_s)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(INSP_HDR_STEP + 6, d);
	sl = (t_islider){"SX", 0.01, max_s, &gui->transform.scale.x,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"SY", 0.01, max_s, &gui->transform.scale.y,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"SZ", 0.01, max_s, &gui->transform.scale.z,
		transform_selection_sync};
	if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl))
		return (true);
	return (false);
}

bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	p;
	t_vec2s	d;
	float	max_s;

	if (!gui->selection.active)
		return (false);
	max_s = 100.0f;
	if (gui->selection.type == TYPE_MESH)
		max_s = 10.0f;
	d = gui->win.disp_size;
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(92 + INSP_HDR_STEP, d);
	if (try_tr_pos(gui, mouse, &p))
		return (true);
	if (try_tr_rot(gui, mouse, &p))
		return (true);
	if (try_tr_scale(gui, mouse, &p, max_s))
		return (true);
	return (false);
}

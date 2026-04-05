/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:15:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_pos_sliders(t_gui *gui, t_vec3 *v, t_vec2i *p)
{
	t_vec2i		d;
	t_islider	sl;

	d = gui->win.disp_size;
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Position");
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"X", SL_POS_MIN, SL_POS_MAX, &v->x, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Y", SL_POS_MIN, SL_POS_MAX, &v->y, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Z", SL_POS_MIN, SL_POS_MAX, &v->z, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	build_rot_sliders(t_gui *gui, t_rotator *r, t_vec2i *p)
{
	t_vec2i		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Rotation");
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"Pitch", -180.0, 180.0, &r->pitch, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Yaw", -180.0, 180.0, &r->yaw, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Roll", -180.0, 180.0, &r->roll, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	build_scale_sliders(t_gui *gui, t_vec3 *v, float max_s, t_vec2i *p)
{
	t_vec2i		d;
	t_islider	sl;

	d = gui->win.disp_size;
	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Scale");
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"SX", 0.01, max_s, &v->x, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"SY", 0.01, max_s, &v->y, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"SZ", 0.01, max_s, &v->z, transform_selection_sync};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

void	build_tr_sliders(t_gui *gui, int type, t_vec2i *p)
{
	float	max_s;

	max_s = 100.0f;
	if (type == TYPE_MESH)
		max_s = 10.0f;
	build_pos_sliders(gui, &gui->transform.pos, p);
	build_rot_sliders(gui, &gui->transform.rotation, p);
	build_scale_sliders(gui, &gui->transform.scale, max_s, p);
}


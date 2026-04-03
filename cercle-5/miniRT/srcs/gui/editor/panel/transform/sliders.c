/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:17:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_pos_sliders(t_gui *gui, t_vec3 *v, t_vec2i *p)
{
	t_islider	sl;

	gui_label(gui, "Position", (t_vec2i){p->x, p->y += 25});
	sl = (t_islider){"X", -100, 100, &v->x, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 25}, sl);
	sl = (t_islider){"Y", -100, 100, &v->y, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
	sl = (t_islider){"Z", -100, 100, &v->z, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
}

static void	build_rot_sliders(t_gui *gui, t_rotator *r, t_vec2i *p)
{
	t_islider	sl;

	gui_label(gui, "Rotation", (t_vec2i){p->x, p->y += 35});
	sl = (t_islider){"Pitch", -PI, PI, &r->pitch, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 25}, sl);
	sl = (t_islider){"Yaw", -PI, PI, &r->yaw, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
	sl = (t_islider){"Roll", -PI, PI, &r->roll, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
}

static void	build_scale_sliders(t_gui *gui, t_vec3 *v, float max_s, t_vec2i *p)
{
	t_islider	sl;

	gui_label(gui, "Scale", (t_vec2i){p->x, p->y += 35});
	sl = (t_islider){"SX", 0.01, max_s, &v->x, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 25}, sl);
	sl = (t_islider){"SY", 0.01, max_s, &v->y, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
	sl = (t_islider){"SZ", 0.01, max_s, &v->z, transform_selection_sync};
	draw_slider_row(gui, (t_vec2i){p->x + 8, p->y += 30}, sl);
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

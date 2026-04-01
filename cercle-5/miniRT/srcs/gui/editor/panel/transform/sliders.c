/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_pos_sliders(t_gui *gui, t_vec3 *v, int *y)
{
	gui_label(gui, "Position", (t_vec2i){10, *y += 25});
	gui_slider(gui, &v->x, -100, 100, (t_vec2i){10, *y += 25}, "X: %.2f");
	gui_slider(gui, &v->y, -100, 100, (t_vec2i){10, *y += 20}, "Y: %.2f");
	gui_slider(gui, &v->z, -100, 100, (t_vec2i){10, *y += 20}, "Z: %.2f");
}

static void	build_rot_sliders(t_gui *gui, t_rotator *r, int *y)
{
	gui_label(gui, "Rotation", (t_vec2i){10, *y += 25});
	gui_slider(gui, &r->pitch, -PI, PI, (t_vec2i){10, *y += 25}, "Pitch: %.2f");
	gui_slider(gui, &r->yaw,   -PI, PI, (t_vec2i){10, *y += 20}, "Yaw:   %.2f");
	gui_slider(gui, &r->roll,  -PI, PI, (t_vec2i){10, *y += 20}, "Roll:  %.2f");
}

static void	build_scale_sliders(t_gui *gui, t_vec3 *v, float max_s, int *y)
{
	gui_label(gui, "Scale", (t_vec2i){10, *y += 25});
	gui_slider(gui, &v->x, 0.01, max_s, (t_vec2i){10, *y += 25}, "SX: %.2f");
	gui_slider(gui, &v->y, 0.01, max_s, (t_vec2i){10, *y += 20}, "SY: %.2f");
	gui_slider(gui, &v->z, 0.01, max_s, (t_vec2i){10, *y += 20}, "SZ: %.2f");
}

void	build_tr_sliders(t_gui *gui, int type, int *y)
{
	float	max_s;

	max_s = 100.0f;
	if (type == TYPE_MESH)
		max_s = 10.0f;
	build_pos_sliders(gui, &gui->transform.pos, y);
	build_rot_sliders(gui, &gui->transform.rotation, y);
	build_scale_sliders(gui, &gui->transform.scale, max_s, y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 21:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	try_tr_pos(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_islider	sl;

	sl = (t_islider){"X", -100, 100, &gui->transform.pos.x};
	p->y += 25;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"Y", -100, 100, &gui->transform.pos.y};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"Z", -100, 100, &gui->transform.pos.z};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	return (false);
}

static bool	try_tr_rot(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_islider	sl;

	sl = (t_islider){"Pitch", -PI, PI, &gui->transform.rotation.pitch};
	p->y += 25;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"Yaw", -PI, PI, &gui->transform.rotation.yaw};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"Roll", -PI, PI, &gui->transform.rotation.roll};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	return (false);
}

static bool	try_tr_scale(t_gui *gui, t_vec2i mouse, t_vec2i *p, float max_s)
{
	t_islider	sl;

	sl = (t_islider){"SX", 0.01, max_s, &gui->transform.scale.x};
	p->y += 25;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"SY", 0.01, max_s, &gui->transform.scale.y};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	sl = (t_islider){"SZ", 0.01, max_s, &gui->transform.scale.z};
	p->y += 30;
	if (try_islider_click(gui, mouse, (t_vec2i){p->x + 8, p->y}, sl,
		transform_selection_sync))
		return (true);
	return (false);
}

bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	p;
	float	max_s;

	if (!gui->selection.active)
		return (false);
	max_s = 100.0f;
	if (gui->selection.type == TYPE_MESH)
		max_s = 10.0f;
	p = (t_vec2i){gui->win.disp_size.x - gui->inspector.width + 8, 88};
	p = (t_vec2i){p.x - 8, p.y + 25};
	if (try_tr_pos(gui, mouse, &p))
		return (true);
	p.y += 35;
	if (try_tr_rot(gui, mouse, &p))
		return (true);
	p.y += 35;
	if (try_tr_scale(gui, mouse, &p, max_s))
		return (true);
	return (false);
}

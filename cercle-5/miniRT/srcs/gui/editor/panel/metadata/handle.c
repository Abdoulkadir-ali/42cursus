/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 16:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	is_prim_meta_type(t_type type)
{
	if (type == TYPE_SPHERE || type == TYPE_PLANE || type == TYPE_CYLINDER
		|| type == TYPE_CONE || type == TYPE_TRI || type == TYPE_RECT
		|| type == TYPE_PYRAMID || type == TYPE_BOX || type == TYPE_CAPSULE)
		return (true);
	return (false);
}

static void	prim_meta_reset(t_scene *s, int idx)
{
	t_primitive_metadata	*m;

	if (!s->prim_meta)
		return ;
	m = &s->prim_meta[idx];
	s->primitives.px[idx] = m->orig_px;
	s->primitives.py[idx] = m->orig_py;
	s->primitives.pz[idx] = m->orig_pz;
	s->primitives.ax[idx] = m->orig_ax;
	s->primitives.ay[idx] = m->orig_ay;
	s->primitives.az[idx] = m->orig_az;
	s->primitives.radii[idx] = m->orig_radii;
	s->primitives.heights[idx] = m->orig_heights;
}

bool	metadata_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	int	idx;
	int	x;

	if (!gui->scene || !gui->selection->active)
		return (false);
	if (!is_prim_meta_type(gui->selection->type))
		return (false);
	idx = gui->selection->index;
	if (idx < 0 || (size_t)idx >= gui->scene->primitives.count)
		return (false);
	x = gui->win.disp_size.x - gui->inspector->box.size.x;
	if (!phit(mouse, (t_gui_box){vec2i(x + 8, 244), vec2i(148, 20)}))
		return (false);
	prim_meta_reset(gui->scene, idx);
	primitive_transform_sync(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 14:56:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	fill_scale(t_gui *gui, int idx)
{
	t_primitive_array	*p;
	t_type				ty;

	p = &gui->scene->primitives;
	ty = gui->selection->type;
	gui->scratch_tr.scale = vec3(1.0, 1.0, 1.0);
	if (ty == TYPE_SPHERE)
		gui->scratch_tr.scale.x = p->radii[idx];
	else if (ty == TYPE_BOX || ty == TYPE_PYRAMID)
	{
		gui->scratch_tr.scale.x = p->ex[idx];
		gui->scratch_tr.scale.y = p->ey[idx];
		gui->scratch_tr.scale.z = p->ez[idx];
	}
	else if (ty == TYPE_CYLINDER || ty == TYPE_CONE || ty == TYPE_CAPSULE)
	{
		gui->scratch_tr.scale.x = p->radii[idx];
		gui->scratch_tr.scale.y = p->heights[idx];
	}
}

t_transform	*get_selected_transform(t_gui *gui)
{
	t_selection			*sel;
	t_primitive_array	*p;
	int					idx;

	sel = gui->selection;
	if (!sel->active || !gui->scene)
		return (NULL);
	idx = sel->index;
	if (sel->type == gui->scratch_type && idx == gui->scratch_idx)
		return (&gui->scratch_tr);
	p = &gui->scene->primitives;
	gui->scratch_tr.pos = vec3(p->px[idx], p->py[idx], p->pz[idx]);
	gui->scratch_tr.rotation.pitch = 0;
	gui->scratch_tr.rotation.yaw = 0;
	gui->scratch_tr.rotation.roll = 0;
	fill_scale(gui, idx);
	gui->scratch_idx = idx;
	gui->scratch_type = sel->type;
	return (&gui->scratch_tr);
}

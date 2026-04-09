/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	get_primitive_slot_p1(t_selection *sel, t_scene *sc)
{
	if (sel->type == TYPE_SPHERE && sel->index.i < sc->sphere_count)
		return (sc->spheres[sel->index.i].active_slot);
	if (sel->type == TYPE_PLANE && sel->index.i < sc->plane_count)
		return (sc->planes[sel->index.i].active_slot);
	if (sel->type == TYPE_CYLINDER && sel->index.i < sc->cylinder_count)
		return (sc->cylinders[sel->index.i].active_slot);
	if (sel->type == TYPE_CONE && sel->index.i < sc->cone_count)
		return (sc->cones[sel->index.i].active_slot);
	if (sel->type == TYPE_TRI && sel->index.i < sc->tri_count)
		return (sc->tris[sel->index.i].active_slot);
	return (-1);
}

int	get_selected_group_slot(t_gui *gui)
{
	t_selection		*sel;
	t_scene			*sc;
	int				res;

	sel = &gui->selection;
	sc = gui->scene;
	if (!sel->active)
		return (0);
	res = get_primitive_slot_p1(sel, sc);
	if (res != -1)
		return (res);
	if (sel->type == TYPE_RECT && sel->index.i < sc->rect_count)
		return (sc->rects[sel->index.i].active_slot);
	if (sel->type == TYPE_PYRAMID && sel->index.i < sc->pyramid_count)
		return (sc->pyramids[sel->index.i].active_slot);
	if (sel->type == TYPE_BOX && sel->index.i < sc->box_count)
		return (sc->boxes[sel->index.i].active_slot);
	if (sel->type == TYPE_CAPSULE && sel->index.i < sc->capsule_count)
		return (sc->capsules[sel->index.i].active_slot);
	if (sel->type == TYPE_MESH && sel->index.i < sc->group_count)
		return (sc->meshes[sc->groups[sel->index.i].start].active_slot);
	return (0);
}

static void	set_slot_primitives(t_gui *gui, int slot)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
		sc->spheres[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_PLANE)
		sc->planes[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_CYLINDER)
		sc->cylinders[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_CONE)
		sc->cones[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_TRI)
		sc->tris[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_RECT)
		sc->rects[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_PYRAMID)
		sc->pyramids[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_BOX)
		sc->boxes[sel->index.i].active_slot = slot;
	else if (sel->type == TYPE_CAPSULE)
		sc->capsules[sel->index.i].active_slot = slot;
}

void	set_selected_group_slot(t_gui *gui, int slot)
{
	t_selection		*sel;
	t_scene			*sc;
	t_mesh_group	*g;
	size_t			i;

	sel = &gui->selection;
	sc = gui->scene;
	if (!sel->active)
		return ;
	if (sel->type == TYPE_MESH && sel->index.i < sc->group_count)
	{
		g = &sc->groups[sel->index.i];
		i = 0;
		while (i < g->sub_count)
		{
			sc->meshes[g->start + i].active_slot = slot;
			i++;
		}
		return ;
	}
	set_slot_primitives(gui, slot);
}

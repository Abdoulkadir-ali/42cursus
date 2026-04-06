/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 18:19:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_index	mat_id_extra(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	t_mesh		*m;
	size_t		s;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_PYRAMID)
	{
		s = sc->pyramids[sel->index.i].active_slot;
		return (init_index(sc->pyramids[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_BOX)
	{
		s = sc->boxes[sel->index.i].active_slot;
		return (init_index(sc->boxes[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_CAPSULE)
	{
		s = sc->capsules[sel->index.i].active_slot;
		return (init_index(sc->capsules[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_MESH && sel->index.i < sc->group_count)
	{
		m = &sc->meshes[sc->groups[sel->index.i].start];
		return (init_index(m->mat_slots[m->active_slot], false));
	}
	return (init_index(0, true));
}

static t_index	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	size_t		s;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
	{
		s = sc->spheres[sel->index.i].active_slot;
		return (init_index(sc->spheres[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_PLANE)
	{
		s = sc->planes[sel->index.i].active_slot;
		return (init_index(sc->planes[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_CYLINDER)
	{
		s = sc->cylinders[sel->index.i].active_slot;
		return (init_index(sc->cylinders[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_CONE)
	{
		s = sc->cones[sel->index.i].active_slot;
		return (init_index(sc->cones[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_TRI)
	{
		s = sc->tris[sel->index.i].active_slot;
		return (init_index(sc->tris[sel->index.i].mat_slots[s], false));
	}
	if (sel->type == TYPE_RECT)
	{
		s = sc->rects[sel->index.i].active_slot;
		return (init_index(sc->rects[sel->index.i].mat_slots[s], false));
	}
	return (mat_id_extra(gui));
}

t_material	*get_selected_material(t_gui *gui)
{
	t_selection	*sel;
	t_index		idx;

	sel = &gui->selection;
	if (!sel->active || !gui->scene)
		return (NULL);
	idx = mat_id_of_selection(gui);
	if (idx.error || idx.i >= gui->scene->mat_count)
		return (NULL);
	return (&gui->scene->materials[idx.i]);
}


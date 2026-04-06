/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_index	mat_id_extra(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_PYRAMID)
		return (init_index(sc->pyramids[sel->index.i].mat_id, false));
	if (sel->type == TYPE_BOX)
		return (init_index(sc->boxes[sel->index.i].mat_id, false));
	if (sel->type == TYPE_CAPSULE)
		return (init_index(sc->capsules[sel->index.i].mat_id, false));
	if (sel->type == TYPE_MESH && sel->index.i < sc->group_count)
		return (init_index(sc->meshes[sc->groups[sel->index.i].mesh_start].mat_id,
				false));
	return (init_index(0, true));
}

static t_index	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
		return (init_index(sc->spheres[sel->index.i].mat_id, false));
	if (sel->type == TYPE_PLANE)
		return (init_index(sc->planes[sel->index.i].mat_id, false));
	if (sel->type == TYPE_CYLINDER)
		return (init_index(sc->cylinders[sel->index.i].mat_id, false));
	if (sel->type == TYPE_CONE)
		return (init_index(sc->cones[sel->index.i].mat_id, false));
	if (sel->type == TYPE_TRI)
		return (init_index(sc->tris[sel->index.i].mat_id, false));
	if (sel->type == TYPE_RECT)
		return (init_index(sc->rects[sel->index.i].mat_id, false));
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

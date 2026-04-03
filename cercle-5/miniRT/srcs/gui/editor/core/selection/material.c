/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:47:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
		return (sc->spheres[sel->index].mat_id);
	if (sel->type == TYPE_PLANE)
		return (sc->planes[sel->index].mat_id);
	if (sel->type == TYPE_CYLINDER)
		return (sc->cylinders[sel->index].mat_id);
	if (sel->type == TYPE_CONE)
		return (sc->cones[sel->index].mat_id);
	if (sel->type == TYPE_TRI)
		return (sc->tris[sel->index].mat_id);
	if (sel->type == TYPE_RECT)
		return (sc->rects[sel->index].mat_id);
	if (sel->type == TYPE_PYRAMID)
		return (sc->pyramids[sel->index].mat_id);
	if (sel->type == TYPE_BOX)
		return (sc->boxes[sel->index].mat_id);
	if (sel->type == TYPE_CAPSULE)
		return (sc->capsules[sel->index].mat_id);
	if (sel->type == TYPE_MESH && 1
		&& sel->index < sc->group_count)
		return (sc->meshes[sc->groups[sel->index].start].mat_id);
	return (-1);
}

t_material	*get_selected_material(t_gui *gui)
{
	t_selection	*sel;
	int			mat_id;

	sel = &gui->selection;
	if (!sel->active || !gui->scene)
		return (NULL);
	mat_id = mat_id_of_selection(gui);
	if ((size_t)mat_id >= gui->scene->mat_count)
		return (NULL);
	return (&gui->scene->materials[mat_id]);
}

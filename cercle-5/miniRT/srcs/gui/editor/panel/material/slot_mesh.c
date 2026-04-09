/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_mesh	*selected_fdf_mesh(t_gui *gui)
{
	t_selection		*sel;
	t_scene			*sc;
	t_mesh_group	*g;
	t_mesh			*m;

	sel = &gui->selection;
	sc = gui->scene;
	if (!sel->active || sel->type != TYPE_MESH
		|| sel->index.i >= sc->group_count)
		return (NULL);
	g = &sc->groups[sel->index.i];
	m = &sc->meshes[g->start];
	if (!m->is_fdf)
		return (NULL);
	return (m);
}

t_mesh	*get_selected_fdf_mesh(t_gui *gui)
{
	return (selected_fdf_mesh(gui));
}

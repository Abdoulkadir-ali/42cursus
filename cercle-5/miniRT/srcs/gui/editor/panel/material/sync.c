/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sync_group_materials(t_gui *gui)
{
	t_selection		*sel;
	t_mesh_group	*g;
	t_material		*lead;
	int				si;
	int				mat_id;

	sel = &gui->selection;
	if (!sel->active || sel->type != TYPE_MESH)
		return ;
	g = &gui->scene->groups[sel->index];
	lead = &gui->scene->materials[gui->scene->meshes[g->start].mat_id];
	si = 0;
	while (++si < g->sub_count)
	{
		mat_id = gui->scene->meshes[g->start + si].mat_id;
		if (mat_id >= 0 && mat_id < gui->scene->mat_count)
			gui->scene->materials[mat_id] = *lead;
	}
}

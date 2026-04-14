/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 11:28:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sync_group_materials(t_gui *gui)
{
	t_selection		*sel;
	t_mesh_group	*g;
	t_material		*lead;
	size_t			i;
	size_t			mat_id;

	sel = &gui->selection;
	if (!sel->active || sel->type != TYPE_MESH)
		return ;
	g = &gui->scene->groups[sel->index.i];
	lead = &gui->scene->materials[gui->scene->meshes[g->start].mat_id];
	i = 0;
	while (i < g->sub_count)
	{
		mat_id = gui->scene->meshes[g->start + i++].mat_id;
		if (mat_id < gui->scene->mat_count)
			gui->scene->materials[mat_id] = *lead;
	}
}

void	sync_temperature(t_gui *gui)
{
	t_material	*mat;

	mat = get_selected_material(gui);
	if (mat)
		apply_blackbody_to_mat(mat);
	sync_group_materials(gui);
	if (gui->scene && gui->scene->bvh)
		build_emissive_cache(gui->scene);
}

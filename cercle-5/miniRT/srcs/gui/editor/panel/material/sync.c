/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 14:59:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sync_group_materials(t_gui *gui)
{
	t_selection		*sel;
	t_mesh_group	*g;
	t_material		*lead;
	size_t			si;
	size_t			mat_id;

	sel = &gui->selection;
	if (!sel->active || sel->type != TYPE_MESH)
		return ;
	g = &gui->scene->groups[sel->index];
	lead = &gui->scene->materials[gui->scene->meshes[g->start].mat_id];
	si = 0;
	while (++si < g->sub_count)
	{
		t_cmd	_c;

		mat_id = gui->scene->meshes[g->start + si].mat_id;
		if (mat_id < gui->scene->mat_count)
		{
			ft_memset(&_c, 0, sizeof(_c));
			_c.type = CMD_SET_MATERIAL;
			_c.data.material.mat_id = mat_id;
			_c.data.material.material = *lead;
			cmd_enqueue(gui, _c);
		}
	}
}

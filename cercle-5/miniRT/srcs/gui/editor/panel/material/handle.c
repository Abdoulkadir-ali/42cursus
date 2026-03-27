/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	sync_group_materials(t_gui *gui)
{
	t_selection		*sel;
	t_mesh_group	*g;
	t_material		*lead;
	int				si;
	int				mat_id;

	sel = gui->selection;
	if (!sel->active || sel->type != TYPE_MESH)
		return ;
	g = &gui->scene->groups[sel->index];
	lead = &gui->scene->materials[gui->scene->meshes[g->start].mat_id];
	si = 1;
	while (si < g->sub_count)
	{
		mat_id = gui->scene->meshes[g->start + si].mat_id;
		if (mat_id >= 0 && mat_id < gui->scene->mat_count)
			gui->scene->materials[mat_id] = *lead;
		si++;
	}
}

static void	material_sync_invalidate(t_gui *gui)
{
	sync_group_materials(gui);
	scene_invalidate(gui->scene);
}

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;
	int			x;

	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	x = gui->win.disp_w - gui->inspector->width;
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = -1;
	while (++i < count)
	{
		if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(x + 8, y),
				sl[i], material_sync_invalidate}))
			return (true);
		y += 30;
	}
	return (false);
}


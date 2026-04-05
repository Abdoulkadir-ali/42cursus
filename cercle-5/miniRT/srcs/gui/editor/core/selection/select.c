/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:24:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	rebuild_bvh(t_gui *gui)
{
	t_bvh	*old;

	pthread_rwlock_wrlock(&gui->scene->bvh_lock);
	old = gui->scene->bvh;
	gui->scene->bvh = NULL;
	pthread_rwlock_unlock(&gui->scene->bvh_lock);
	bvh_destroy(old);
	old = bvh_create(gui->scene);
	pthread_rwlock_wrlock(&gui->scene->bvh_lock);
	gui->scene->bvh = old;
	pthread_rwlock_unlock(&gui->scene->bvh_lock);
}

static void	set_selection_bbox(t_gui *gui, t_type type, size_t index)
{
	t_aabb			union_bbox;
	t_mesh_group	*g;
	t_bvh_ref		ref;
	size_t			si;

	if (type == TYPE_MESH && index < gui->scene->group_count)
	{
		g = &gui->scene->groups[index];
		union_bbox = gui->scene->meshes[g->start].bbox;
		si = 0;
		while (++si < g->sub_count)
			union_bbox = aabb_union(&union_bbox,
					&gui->scene->meshes[g->start + si].bbox);
		gui->selection.bbox = union_bbox;
	}
	else
	{
		ref.type = (uint8_t)type;
		ref.index = index;
		gui->selection.bbox = aabb_from_ref(gui->scene, ref);
	}
}

static void	set_inspector_tab(t_gui *gui, t_type type)
{
	gui->inspector.visible = true;
	if (type == TYPE_MESH)
		gui->inspector.tab = TAB_INFO;
	else if (type == TYPE_LIGHT)
		gui->inspector.tab = TAB_LIGHT;
	else
		gui->inspector.tab = TAB_TRANSFORM;
}

void	select_object(t_gui *gui, t_type type, size_t index)
{
	gui->selection.type = type;
	gui->selection.index = index;
	gui->selection.active = true;
	set_selection_bbox(gui, type, index);
	set_inspector_tab(gui, type);
	transform_panel_sync(gui);
}

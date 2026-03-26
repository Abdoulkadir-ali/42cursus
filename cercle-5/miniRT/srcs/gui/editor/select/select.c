/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:40:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "raytracing.h"

void	select_object(t_gui *gui, t_type type, int index)
{
    t_aabb			union_bbox;
    t_mesh_group	*g;
    int			si;

    gui->selection.type = type;
    gui->selection.index = index;
    gui->selection.active = true;
    /* For mesh groups compute the union bbox directly; for everything else
    ** keep using aabb_from_ref (which still operates on flat mesh indices). */
    if (type == TYPE_MESH && index >= 0 && index < gui->scene->group_count)
    {
        g = &gui->scene->groups[index];
        union_bbox = gui->scene->meshes[g->start].bbox;
        si = 1;
        while (si < g->sub_count)
        {
            union_bbox = aabb_union(&union_bbox,
                    &gui->scene->meshes[g->start + si].bbox);
            si++;
        }
        gui->selection.bbox = union_bbox;
    }
    else
    {
        t_bvh_ref	ref;

        ref.type = (uint8_t)type;
        ref.index = index;
        gui->selection.bbox = aabb_from_ref(gui->scene, ref);
    }
    gui->inspector.visible = true;
    if (type == TYPE_MESH)
        gui->inspector.tab = TAB_INFO;
    else if (type == TYPE_LIGHT)
        gui->inspector.tab = TAB_LIGHT;
    else
        gui->inspector.tab = TAB_TRANSFORM;
    ft_print_debug("[editor] selected %d idx=%d\n", (int)type, index);
}
